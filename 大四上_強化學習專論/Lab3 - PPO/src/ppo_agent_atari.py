import torch
import torch.nn as nn
import numpy as np
import os
import time
from collections import deque
from torch.utils.tensorboard import SummaryWriter
from replay_buffer.gae_replay_buffer import GaeSampleMemory
from base_agent import PPOBaseAgent
from models.atari_model import AtariNet
import gym
from torch.distributions import Categorical


class AtariPPOAgent(PPOBaseAgent):
	def __init__(self, config):
		super(AtariPPOAgent, self).__init__(config)
		### TODO ###
		# initialize env
		self.env = gym.make(config['env_id'])
		self.env = gym.wrappers.GrayScaleObservation(self.env)
		self.env = gym.wrappers.ResizeObservation(self.env, 84)
		self.env = gym.wrappers.FrameStack(self.env, 4)
		self.env.seed(0)
		### TODO ###
		# initialize test_env
		self.test_env = gym.make(config['env_id'])
		#self.test_env = gym.make(config['env_id'],render_mode="rgb_array")
		#self.test_env = gym.wrappers.RecordVideo(self.test_env, 'video')
		self.test_env = gym.wrappers.GrayScaleObservation(self.test_env)
		self.test_env = gym.wrappers.ResizeObservation(self.test_env, 84)
		self.test_env = gym.wrappers.FrameStack(self.test_env, 4)
		self.test_env.seed(0)

		self.net = AtariNet(self.env.action_space.n)
		self.net.to(self.device)
		self.lr = config["learning_rate"]
		self.update_count = config["update_ppo_epoch"]
		self.optim = torch.optim.Adam(self.net.parameters(), lr=self.lr)
		
	def decide_agent_actions(self, observation, eval=False):
		### TODO ###
		# add batch dimension in observation
		# get action, value, logp from net
		observation = np.array(observation, dtype=np.float32)
		observation = torch.tensor(observation,dtype=torch.float32).squeeze(-1).unsqueeze(0).to(self.device)
		
		if eval:
			with torch.no_grad():
				action, value, logp_pi,_ = self.net(observation, eval=True)
		else:
			action, value, logp_pi,_ = self.net(observation)
		
		return action, value, logp_pi


	
	def update(self):
		loss_counter = 0.0001
		total_surrogate_loss = 0
		total_v_loss = 0
		total_entropy = 0
		total_loss = 0

		batches = self.gae_replay_buffer.extract_batch(self.discount_factor_gamma, self.discount_factor_lambda)
		sample_count = len(batches["action"])
		batch_index = np.random.permutation(sample_count)
		
		observation_batch = {}
		for key in batches["observation"]:
			observation_batch[key] = batches["observation"][key][batch_index]
		action_batch = batches["action"][batch_index]
		return_batch = batches["return"][batch_index]
		adv_batch = batches["adv"][batch_index]
		v_batch = batches["value"][batch_index]
		logp_pi_batch = batches["logp_pi"][batch_index]

		for _ in range(self.update_count):
			for start in range(0, sample_count, self.batch_size):
				ob_train_batch = {}
				for key in observation_batch:
					ob_train_batch[key] = observation_batch[key][start:start + self.batch_size]
				ac_train_batch = action_batch[start:start + self.batch_size]
				return_train_batch = return_batch[start:start + self.batch_size]
				adv_train_batch = adv_batch[start:start + self.batch_size]
				v_train_batch = v_batch[start:start + self.batch_size]
				logp_pi_train_batch = logp_pi_batch[start:start + self.batch_size]

				ob_train_batch = torch.from_numpy(ob_train_batch["observation_2d"])
				ob_train_batch = ob_train_batch.to(self.device, dtype=torch.float32)
				ac_train_batch = torch.from_numpy(ac_train_batch)
				ac_train_batch = ac_train_batch.to(self.device, dtype=torch.long)
				adv_train_batch = torch.from_numpy(adv_train_batch)
				adv_train_batch = adv_train_batch.to(self.device, dtype=torch.float32)
				logp_pi_train_batch = torch.from_numpy(logp_pi_train_batch)
				logp_pi_train_batch = logp_pi_train_batch.to(self.device, dtype=torch.float32)
				return_train_batch = torch.from_numpy(return_train_batch)
				return_train_batch = return_train_batch.to(self.device, dtype=torch.float32)


				### TODO ###				
				# calculate loss and update network
				action, value_pi, logp_pi, entropy = self.net(ob_train_batch.squeeze())
				entropy = entropy.mean()

				# calculate policy loss
				x = ob_train_batch.squeeze().float() / 255.
				x = self.net.cnn(x)
				x = torch.flatten(x, start_dim=1)
				action_logits_output = self.net.action_logits(x)
				dist = Categorical(logits=action_logits_output)
				log_probs = dist.log_prob(ac_train_batch.squeeze())
				#print(action_logits_output)
				#print("train batch shape: ",ac_train_batch.shape)
				#log_probs = action_logits_output.gather(1, ac_train_batch)

# 				print("log_probs",log_probs.shape)
# 				print("log_pi",logp_pi_train_batch.shape)
				ratio = torch.exp(log_probs-logp_pi_train_batch)
				surrogate_loss = torch.min(ratio * adv_train_batch, 
							   				torch.clamp(ratio, 1.0 - self.clip_epsilon, 1.0 + self.clip_epsilon) * adv_train_batch)
				surrogate_loss = -surrogate_loss.mean()

				# calculate value loss
				value_criterion = nn.MSELoss()
				v_loss = value_criterion(value_pi,return_train_batch)
				
				# calculate total loss
				loss = surrogate_loss + self.value_coefficient * v_loss - self.entropy_coefficient * entropy

				# update network
				self.optim.zero_grad()
				loss.backward()
				nn.utils.clip_grad_norm_(self.net.parameters(), self.max_gradient_norm)
				self.optim.step()

				total_surrogate_loss += surrogate_loss.item()
				total_v_loss += v_loss.item()
				total_entropy += entropy.item()
				total_loss += loss.item()
				loss_counter += 1

		self.writer.add_scalar('PPO/Loss', total_loss / loss_counter, self.total_time_step)
		self.writer.add_scalar('PPO/Surrogate Loss', total_surrogate_loss / loss_counter, self.total_time_step)
		self.writer.add_scalar('PPO/Value Loss', total_v_loss / loss_counter, self.total_time_step)
		self.writer.add_scalar('PPO/Entropy', total_entropy / loss_counter, self.total_time_step)
		print(f"Loss: {total_loss / loss_counter}\
			\nSurrogate Loss: {total_surrogate_loss / loss_counter}\
			\nValue Loss: {total_v_loss / loss_counter}\
			\nEntropy: {total_entropy / loss_counter}\
			")
	



