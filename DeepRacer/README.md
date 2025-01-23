# Gradient Descent Batch Size:- 
Number of recent vehicle experiences. More value == more stable the training.

# Number of Epochs:- 
How many times to go through the training data. Related to Batch Size.

# Learning Rate:- 
The size of update during each training cycle. Bigger update == Bigger change to the model. Possible overshooting result. Too high not going to converge.

# Entropy:- 
How much randomness is introduced into the action the car going to take. For exploration, to find most optimum path. It need try different things from the model updates. (At beginning better a lot. Too few agent won't learn)

# Discount Factor:- 
How many steps the agent is going to look ahead when trying to make a decision through an episode. Take into account where it will be. 

# Loss Type:- 
Huber and Mean squared error. 

# Number of epsiodes between policy updates:- 
Episodes are attempts for agent to get around the track. Number of episodes determine how many attempts it made before it switches to training process. More value ==  more epxerience data.


# Strat:

1) Start with default settings
2) Make small changes
3) Keep train time short, clone model
4) Keep detailed notes. Outline what changes are made and the measureable effect of training process.
5) Use the logs. (Jupyter notebook log(?))
6) Start aggressive and get model to learn as quick as possible. Then tone the hyperparams down to prevent overshooting.





