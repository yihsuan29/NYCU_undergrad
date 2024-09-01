import torch
import torch.nn as nn
import numpy as np
import os
import time
from collections import deque
from torch.utils.tensorboard import SummaryWriter
from replay_buffer.gae_replay_buffer import GaeSampleMemory
from replay_buffer.replay_buffer import ReplayMemory
from abc import ABC, abstractmethod

class PPOBaseAgent(ABC):
	def __init__(self, config):
		self.gpu = config["gpu"]
		self.device = torch.device("cuda" if self.gpu and torch.cuda.is_available() else "cpu")
		self.total_time_step = 0
		self.training_steps = int(config["training_steps"])
		self.update_sample_count = int(config["update_sample_count"])
		self.discount_factor_gamma = config["discount_factor_gamma"]
		self.discount_factor_lambda = config["discount_factor_lambda"]
		self.clip_epsilon = config["clip_epsilon"]
		self.max_gradient_norm = config["max_gradient_norm"]
		self.batch_size = int(config["batch_size"])
		self.value_coefficient = config["value_coefficient"]
		self.entropy_coefficient = config["entropy_coefficient"]
		self.eval_interval = config["eval_interval"]
		self.eval_episode = config["eval_episode"]

		self.gae_replay_buffer = GaeSampleMemory({
			"horizon" : config["horizon"],
			"use_return_as_advantage": False,
			"agent_count": 1,
			})

		self.writer = SummaryWriter(config["logdir"])

	@abstractmethod
	def decide_agent_actions(self, observation):
		# add batch dimension in observation
		# get action, value, logp from net

		return NotImplementedError

	@abstractmethod
	def update(self):
		# sample a minibatch of transitions
		batches = self.gae_replay_buffer.extract_batch(self.discount_factor_gamma, self.discount_factor_lambda)
		# calculate the loss and update the behavior network

		return NotImplementedError


	def train(self):
		episode_idx = 0
		while self.total_time_step <= self.training_steps:
			# if(self.total_time_step > 1e7 and self.total_time_step <= 2e7):
			# 	self.lr = 2e-4
			# elif(self.total_time_step > 2e7 and self.total_time_step <= 3e7):
			# 	self.lr = 1.5e-4
			# elif(self.total_time_step > 3e7 and self.total_time_step <= 4e7):
			# 	self.lr = 1e-4
			# elif(self.total_time_step > 4e7 and self.total_time_step <= 5e7):
			# 	self.lr = 5e-5
			# elif(self.total_time_step > 5e7):
			# 	self.lr = 2.5e-5
			# self.optim = torch.optim.Adam(self.net.parameters(), lr=self.lr)
			observation, info = self.env.reset()
			episode_reward = 0
			episode_len = 0
			episode_idx += 1
			while True:
				action, value, logp_pi = self.decide_agent_actions(observation)
				next_observation, reward, terminate, truncate, info = self.env.step(action[0])
				# observation must be dict before storing into gae_replay_buffer
				# dimension of reward, value, logp_pi, done must be the same
				# print(action.shape)
				# print(value.shape)
				# print(logp_pi.squeeze().shape)
				# print("-----------")
				obs = {}
				obs["observation_2d"] = np.asarray(observation, dtype=np.float32)
				self.gae_replay_buffer.append(0, {
						"observation": obs,    # shape = (4,84,84)
						"action": action.detach().cpu().numpy(),      # shape = (1,)
						"reward": reward,      # shape = ()
						"value": value.detach().cpu().numpy(),        # shape = ()
						"logp_pi": logp_pi.squeeze().detach().cpu().numpy(),    # shape = ()
						"done": terminate,     # shape = ()
					})

				if len(self.gae_replay_buffer) >= self.update_sample_count:
					self.update()
					self.gae_replay_buffer.clear_buffer()

				episode_reward += reward
				episode_len += 1
				
				if terminate or truncate:
					self.writer.add_scalar('Train/Episode Reward', episode_reward, self.total_time_step)
					self.writer.add_scalar('Train/Episode Len', episode_len, self.total_time_step)
					print(f"[{len(self.gae_replay_buffer)}/{self.update_sample_count}][{self.total_time_step}/{self.training_steps}]  episode: {episode_idx}  episode reward: {episode_reward}  episode len: {episode_len}")
					break
					
				observation = next_observation
				self.total_time_step += 1
				
			if episode_idx % self.eval_interval == 0:
				# save model checkpoint
				avg_score = self.evaluate()
				self.save(os.path.join(self.writer.log_dir, f"model_{self.total_time_step}_{int(avg_score)}.pth"))
				self.writer.add_scalar('Evaluate/Episode Reward', avg_score, self.total_time_step)

	def evaluate(self):
		print("==============================================")
		print("Evaluating...")
		all_rewards = []
        
		for i in range(self.eval_episode):
			observation, info = self.test_env.reset()
			self.test_env.seed(0)
			os.environ['PYTHONHASHSEED'] = str(0)
			torch.manual_seed(0)
			torch.cuda.manual_seed(0)
			torch.backends.cudnn.deterministic = True
			total_reward = 0
			while True:
				#self.test_env.render()
				action, _, _ = self.decide_agent_actions(observation, eval=True)
				next_observation, reward, terminate, truncate, info = self.test_env.step(action[0])
				total_reward += reward
				if terminate or truncate:
					print(f"episode {i+1} reward: {total_reward}")
					all_rewards.append(total_reward)
					break

				observation = next_observation
			

		avg = sum(all_rewards) / self.eval_episode
		print(f"average score: {avg}")
		print("==============================================")
		return avg
	
	# save model
	def save(self, save_path):
		torch.save(self.net.state_dict(), save_path)

	# load model
	def load(self, load_path):
		self.net.load_state_dict(torch.load(load_path))

	# load model weights and evaluate
	def load_and_evaluate(self, load_path):
		self.load(load_path)
		self.evaluate()


	

