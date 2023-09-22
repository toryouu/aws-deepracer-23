zero_val = 0.003

def reward_function(params):
    wp = params['closest_waypoints'][1]
    speed= params['speed']
    
    #Check if car is within range of the waypoint
    if wp in (list(range(59, 82))):
        if speed >= 2:
            return zero_val
    
    return speed

