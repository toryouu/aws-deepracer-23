def reward_function(params):
  
    # Read input parameters
    speed = params['speed']
    wp = params['closest_waypoints'][1]
    
    reward = 30
    
    # Set the speed threshold based your action space
    SPEED_THRESHOLD_FAST = 2.7
    SPEED_THRESHOLD_SLOW = 1.1
    
    # Reward if car go vroom vroom, penalize too slow
    if speed >= SPEED_THRESHOLD_FAST:
        reward += 10
    elif speed <= SPEED_THRESHOLD_SLOW:
        reward += 10
    else:
        reward -= 7
    
    #Check if car is within range of the waypoint (main straight)
    if wp in (list(range(0, 17))) and (list(range(111, 117))):
        if speed >= 3.1:
            reward += 15
    
    #Check if car is within range of the waypoint (parabolica)
    if wp in (list(range(22, 42))):
        if speed <= 1.3:
            reward += 10
            
    #Check if car is within range of the waypoint (ascari to curva lesmo)
    if wp in (list(range(50, 71))):
        if speed <= 2.8:
            reward += 10
    
    #Check if car is within range of the waypoint (curva lesmo to curva grande)
    if wp in (list(range(86, 109))):
        if speed <= 2.2:
            reward += 5
    
    

    return float(reward)
    
