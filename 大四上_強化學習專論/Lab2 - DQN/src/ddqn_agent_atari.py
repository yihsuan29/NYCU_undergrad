import torch
import torch.nn as nn
import numpy as np
from torch.utils.tensorboard import SummaryWriter
from base_agent import DQNBaseAgent
from models.atari_model import AtariNetDQN
import gym
import random

class AtariDDQNAgent(DQNBaseAgent):
	def __init__(self, config):
		super(AtariDDQNAgent, self).__init__(config)
		### TODO ###
		# initialize env
		# self.env = ???
		# TA's hint: (210,160,3) --resize, grayscale--> (84,84) --frame stack--> (84,84,4)
		self.env = gym.make(config['env_id'],render_mode="rgb_array")
		self.env = gym.wrappers.GrayScaleObservation(self.env)
		self.env = gym.wrappers.ResizeObservation(self.env, 84)
		self.env = gym.wrappers.FrameStack(self.env, 4)

		### TODO ###
		# initialize test_env
		# self.test_env = ???
		self.test_env = gym.make(config['env_id'],render_mode="rgb_array")
		self.test_env = gym.wrappers.RecordVideo(self.test_env, 'video')
		self.test_env = gym.wrappers.GrayScaleObservation(self.test_env)
		self.test_env = gym.wrappers.ResizeObservation(self.test_env, 84)
		self.test_env = gym.wrappers.FrameStack(self.test_env, 4)
		self.test_env.seed(0)
		# initialize behavior network and target network
		self.behavior_net = AtariNetDQN(self.env.action_space.n)
		self.behavior_net.to(self.device)
		self.target_net = AtariNetDQN(self.env.action_space.n)
		self.target_net.to(self.device)
		self.target_net.load_state_dict(self.behavior_net.state_dict())
		# initialize optimizer
		self.lr = config["learning_rate"]
		self.optim = torch.optim.Adam(self.behavior_net.parameters(), lr=self.lr, eps=1.5e-4)
		
	def decide_agent_actions(self, observation, epsilon=0.0, action_space=None):
		### TODO ###
		# get action from behavior net, with epsilon-greedy selection
        #  Creating a tensor from a list of numpy.ndarrays is extremely slow. Please consider converting the list to a single numpy
		observation = np.array(observation, dtype=np.float32)
		# observation.shape = (4,84,84,1)
        # shape from (4,84,84,1) --> (4,84,84)
		observation = torch.tensor(observation).squeeze(-1).unsqueeze(0).to(self.device)
        
		if random.random() < epsilon: 
			action = action_space.sample()
		else:
			action = torch.argmax(self.behavior_net(observation)).item() 
		return action    
        
		return NotImplementedError
	
	def update_behavior_network(self):
		# sample a minibatch of transitions
		state, action, reward, next_state, done = self.replay_buffer.sample(self.batch_size, self.device)

		### TODO ###
		# calculate the loss and update the behavior network
		# 1. get Q(s,a) from behavior net
		# 2. get max_a Q(s',a) from target net
		# 3. calculate Q_target = r + gamma * Q(s',max_a Q(s',a) from behavior net) from target net
		# 4. calculate loss between Q(s,a) and Q_target
		# 5. update behavior net
        
		q_value = self.behavior_net(state.squeeze(-1))  
		q_value = q_value.gather(1,action.long())
		with torch.no_grad():
			# select next action based on behavior net
			max_bnet_next = torch.argmax(self.behavior_net(next_state.squeeze(-1)), dim=1)
			q_next = self.target_net(next_state.squeeze(-1)).gather(1,max_bnet_next.unsqueeze(1))
            # if episode terminates at next_state, then q_target = reward           
			q_target = reward + self.gamma* q_next*(1-done)        
		
		criterion = torch.nn.MSELoss()
		loss = criterion(q_value, q_target)

		self.writer.add_scalar('DDQN/Loss', loss.item(), self.total_time_step)

		self.optim.zero_grad()
		loss.backward()
		self.optim.step()
	
	