def reward_function(params):
  
    # Read input parameters
    speed = params['speed']
    
    reward = 30
    
    # Set the speed threshold based your action space
    SPEED_THRESHOLD_FAST = 2.3
    SPEED_THRESHOLD_SLOW = 1.1
    
    # Reward if car go vroom vroom, penalize too slow
    if speed >= SPEED_THRESHOLD_FAST:
        reward += 10
    elif speed <= SPEED_THRESHOLD_SLOW:
        reward += 10
    else:
        reward -= 7



    return float(reward)
    