import math

def reward_function(params):
    ###############################################################################
    '''
    Example of using waypoints and heading to make the car point in the right direction
    '''

    # Read input variables
    all_wheels_on_track = params['all_wheels_on_track']
    waypoints = params['waypoints']
    closest_waypoints = params['closest_waypoints']
    heading = params['heading']
    is_left_of_center = params['is_left_of_center']
    center_variance = params["distance_from_center"] / params["track_width"]

    # Calculate the direction of the center line based on the closest waypoints
    next_point = waypoints[closest_waypoints[1]]
    prev_point = waypoints[closest_waypoints[0]]

    # Racing line
    left_lane = [33,34,35,36,37,38,39,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101]
    center_lane = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,40,41,42,43,44,45,46,47,48,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117]
    right_lane = [49,50,51,52,53,54,55,56]
        
    # Define speed for lane
    fast = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69]
    
    medium = [20,21,22,23,24,25,26,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117]
    
    slow = [28,29,30,31,32,33,34,35,36,37,38,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88]
    
    reward = 30
    
    if params["closest_waypoints"][1] in left_lane and params["is_left_of_center"]:
        reward += 10
    elif params["closest_waypoints"][1] in right_lane and not params["is_left_of_center"]:
        reward += 10
    elif params["closest_waypoints"][1] in center_lane and center_variance < 0.4:
        reward += 10
    else:
        reward -= 10
    
    if params["all_wheels_on_track"]:
        reward += 10
    else:
        reward -= 10

    if params["closest_waypoints"][1] in left_lane and params["is_left_of_center"]:
        reward += 10
    elif params["closest_waypoints"][1] in right_lane and not params["is_left_of_center"]:
        reward += 10
    elif params["closest_waypoints"][1] in center_lane and center_variance < 0.4:
        reward += 10
    else:
        reward -= 10

    if params["closest_waypoints"][1] in fast:
        if params["speed"] > 3.2 :
            reward += 10
        else:
            reward -= 10
    elif params["closest_waypoints"][1] in medium:
        if params["speed"] > 1.4 and params["speed"] <= 2.7 :
            reward += 10
        else:
            reward -= 10
    elif params["closest_waypoints"][1] in slow:
        if params["speed"] <= 1.1 :
            reward += 10
        else:
            reward -= 10
        
    return float(reward)

