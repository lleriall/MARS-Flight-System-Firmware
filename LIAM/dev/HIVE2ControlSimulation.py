import utility
import matplotlib.pyplot as plt
import sys
import time
sys.path.insert(0,'/Users/nyameaama/Documents/MARS-Firmware/LIAM/dev/simulator')
import physics
import visualization
import PID
import trajectoryTrace as trJ

posVector = []

def simulate_system(trajectory):
    mass = 1  # kg
    AOA = 15
    throttle = 100
    # Define PID gains
    kp = 0.5
    ki = 0.1
    kd = 0.7

    # Set initial and target values for vx, vy, and vz
    current_values = trajectory[0]
    target_values = trajectory[1]

    initial_position = (0, 0, 5)
    # Simulation parameters
    dt = 0.1
    duration = 5.0

    # Initialize variables
    integral = [0.0, 0.0, 0.0]
    previous_errors = [0.0, 0.0, 0.0]

    # Simulation loop
    num_steps = int(duration / dt)
    position = initial_position

    for points in range(len(trajectory)):

        for step in range(num_steps):
            # Calculate control signals using PID controller
            control_signals = PID.pid_controller(
                target_values, current_values, kp, ki, kd, integral, previous_errors, dt
            )

            # Update variables for the next iteration
            integral = [PID.calculate_integral(integral[i], control_signals[i], dt) for i in range(3)]
            previous_errors = PID.calculate_error(target_values, current_values)
            current_values = [current_values[i] + control_signals[i] * dt for i in range(3)]

            # Use the control signals in your simulation
            vx_control_signal, vy_control_signal, vz_control_signal = control_signals

            # Update the plane's state
            velocity = (vx_control_signal, vy_control_signal, vz_control_signal)
            print(velocity)
            print(mass)
            
            position, velocityXX = physics.update_plane(mass, position, velocity, AOA, throttle, dt)
            # Get the new position from the updated state
            new_position = position
            #Update trajectory vector for simulation
            posVector.append(new_position)

            #DISPLAY TELEMETRY
            AOA = utility.calculate_angle_of_attack(vx_control_signal, vy_control_signal, vz_control_signal)
            anglesPitch,anglesRoll,anglesYaw = utility.calculate_pitch_roll_yaw(vx_control_signal, vy_control_signal, vz_control_signal)
            print("Pitch:",anglesPitch)
            print("Roll:", anglesRoll)
            print("Yaw:", anglesYaw)

            # Print the current values for debugging
            print("Step:", step+1)
            print("Control signals:", control_signals)
            print("Current values:", current_values)
            print()

            if(utility.has_passed_target(position,target_values) == True):
                nPF = utility.calculate_nearest_forward_point(trajectory, position)
                newV = utility.calculate_velocity(position,nPF)
                target_values = newV
                current_values = position
                break

start_lat = 40.7128  # Latitude of start point
start_lon = -74.0060  # Longitude of start point
end_lat = 34.0522  # Latitude of end point
end_lon = -118.2437  # Longitude of end point
num_points = 10  # Number of points in the generated path
initial_altitude = 20
mid_altitude = 120
final_altitude = 60
num_points = 20

path = trJ.generateCompletePath(start_lat, start_lon, end_lat, end_lon,initial_altitude, mid_altitude, final_altitude, num_points)

flightTrajectory = path
simulate_system(flightTrajectory)
posX, posY, posZ = utility.extractXY(posVector)
# Visualize the trajectory animation
visualization.visualize_trajectory(posX, posY, posZ)