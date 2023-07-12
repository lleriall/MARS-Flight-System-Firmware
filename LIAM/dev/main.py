"""
MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
"""

import utility
import matplotlib.pyplot as plt
import sys
import time
sys.path.insert(0,'/Users/nyameaama/Documents/MARS-Firmware/LIAM/dev/simulator')
import physics
import visualization
import PID

def simulate_system(initial_position, target_values, initial_values, kp, ki, kd, dt, duration):
    mass = 1  # kg
    num_steps = int(duration / dt)
    current_values = initial_values
    integral = [0, 0, 0]
    previous_errors = [0, 0, 0]  # Initialize previous errors for each axis
    AOA = 15
    throttle = 50
    position = initial_position
    posVector = []

    for step in range(num_steps):
        control_signals = PID.pid_controller(
            target_values, current_values, kp, ki, kd, integral, previous_errors, dt
        )

        # Use the control signals in your simulation
        vx_control_signal, vy_control_signal, vz_control_signal = control_signals
        velocity = [vx_control_signal, vy_control_signal, vz_control_signal]
        # Update the plane's state
        position = physics.update_plane(mass, position, velocity, AOA, throttle, dt)

        # Update current values based on the control signals
        current_values[0] += vx_control_signal * dt
        current_values[1] += vy_control_signal * dt
        current_values[2] += vz_control_signal * dt

        # Update integral and previous errors
        errors = PID.calculate_error(target_values, current_values)
        integral = PID.calculate_integral(integral, errors, dt)
        previous_errors = errors

        # Rest of the simulation code
        # Get the new position from the updated state
        new_position = position
        posVector.append(new_position)

    return current_values, posVector

# Define PID gains
kp = 1.0
ki = 0.5
kd = 0.2

# Set initial and target values for vx, vy, and vz
initial_values = [0.0, 0.0, 0.0]
target_values = [10.0, -5.0, 2.0]

initial_position = (0, 0, 5)  # (x, y, z) coordinates

# Simulation parameters
dt = 0.1
duration = 5.0

# Simulate the system with PID control
final_values,finalPos = simulate_system(initial_position,target_values, initial_values, kp, ki, kd, dt, duration)

# Print the final values for vx, vy, and vz
print("Final values: vx =", final_values[0], "vy =", final_values[1], "vz =", final_values[2])

posX, posY, posZ = utility.extractXY(finalPos)
# Visualize the trajectory animation
visualization.visualize_trajectory(posX,posY,posZ)
