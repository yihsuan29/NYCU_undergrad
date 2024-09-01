from td3_agent_CarRacing import CarRacingTD3Agent

if __name__ == '__main__':
	# my hyperparameters, you can change it as you like
	config = {
		"gpu": True,
		"training_steps": 1e7,
		"gamma": 0.99,
		"tau": 0.005,
		"batch_size": 32,
		"warmup_steps": 1000,
		"total_episode": 10000, 
		"lra": 4.5e-6, 
		"lrc": 4.5e-6, 
		"replay_buffer_capacity": 5000,
		"logdir": 'log/CarRacing/test_final/',
		"update_freq": 2,
		"eval_interval": 2,
		"eval_episode": 5,
	}
	agent = CarRacingTD3Agent(config)
	agent.load_and_evaluate('log/CarRacing/test_final/model_8000_892.pth')



