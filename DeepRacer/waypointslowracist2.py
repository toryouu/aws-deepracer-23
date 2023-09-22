first_val = 0.003
second_val = 0.003

def reward_function(params):
    wp = params['closest_waypoints'][1]
    speed= params['speed']
    
    # Give a very low reward by default
    reward = 1e-3
    
    #Check if car is within range of the waypoint (parabolica)
    if wp in (list(range(18, 44))):
        if speed >= 2:
            reward += 5
            return first_val
            
    #Check if car is within range of the waypoint (first lesmo/second lesmo)
    if wp in (list(range(63, 87))):
        if speed >= 2:
            reward += 5
            return second_val

    return float(reward)
    return speed
