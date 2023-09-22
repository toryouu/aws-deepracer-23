import math

def reward_function(params):  


    # Read input variables
    waypoints = params['waypoints']
    closest_waypoints = params['closest_waypoints']
    heading = params['heading']
    speed = params['speed']
    steps = params['steps']
    progress = params['progress']

    # Initialize the reward with typical value
    reward = 1.0
    
    # Calculate the direction of the center line based 
    next_point = waypoints[closest_waypoints[1]]
    prev_point = waypoints[closest_waypoints[0]]

    # Calculate the direction in radius, arctan2(dy, dx), 
    track_direction = math.atan2(next_point[1] - prev_point[1], next_point[0] - prev_point[0])

    # Convert to degree
    track_direction = math.degrees(track_direction)

    # Calculate the difference between the track direction and the heading direction of the car
    direction_diff = abs(track_direction - heading)

    if direction_diff > 180:
        direction_diff = 360 - direction_diff

    # Penalize the reward if the difference is too large
    DIRECTION_THRESHOLD = 10.0

    if direction_diff > DIRECTION_THRESHOLD:
        reward *= 0.5

    # Replace with minimum speed value
    SPEED_THRESHOLD = 1.1

    # Penalize if the car goes too slow
    if speed < SPEED_THRESHOLD:
        reward = reward + 1.0

    # High reward if the car stays on track and goes fast
    else:
        reward = reward + 2.5

    # Total num of steps we want the car to finish the lap, it will vary depends on the track length
    TOTAL_NUM_STEPS = 85

    # Give additional reward if the car pass every 100 steps faster than expected
    if (steps % 100) == 0 and progress > (steps / TOTAL_NUM_STEPS) * 100 :
        reward += 10.0
        
      # Give higher reward if the car completes the track
    if progress > 0.7:
        reward = reward + 2.0
    else:
        reward = 1e-3  # completion % is not good
    
    
    return float(reward)

