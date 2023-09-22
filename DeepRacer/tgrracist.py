def reward_function(params):
    '''
    Example of rewarding the agent to follow center line
    '''
    
    # Read input parameters
    track_width = params['track_width']
    distance_from_center = params['distance_from_center']
    speed = params['speed']
    progress = params['progress']
    abs_steering = abs(params['steering_angle']) # We don't care whether it is left or right steering

    # Change according to minimum speed value
    SPEED_THRESHOLD = 0.7
    
    # Initialize the reward with typical value
    reward = 1.0
    
    # Calculate 3 markers that are at varying distances away from the center line
    marker_1 = 0.1 * track_width
    marker_2 = 0.25 * track_width
    marker_3 = 0.5 * track_width
    
    # Give higher reward if the car is closer to center line and vice versa
    if distance_from_center <= marker_1:
        reward = 1.0
    elif distance_from_center <= marker_2:
        reward = 0.5
    elif distance_from_center <= marker_3:
        reward = 0.1
    else:
        reward = 1e-3  # likely crashed/ close to off track
    
    
    if speed < SPEED_THRESHOLD:
        # Penalize if the car goes too slow
        reward = reward + 0.5
    else:
        # High reward if the car stays on track and goes fast
        reward = reward + 1.0
        
        
    # Give higher reward if the car completes the trac
    if progress > 0.7:
        reward += 2.0
    else:
        reward = 1e-3  # completion % is not goodk
        

    # Penalize if car steer too much to prevent zigzag
    ABS_STEERING_THRESHOLD = 20.0
    if abs_steering > ABS_STEERING_THRESHOLD:
        reward *= 0.8

    return float(reward)