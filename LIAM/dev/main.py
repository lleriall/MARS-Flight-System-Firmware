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

from trace import generate_path
from utility import plot_path
import matplotlib.pyplot as plt
import sys
import time
sys.path.insert(0,'/Users/nyameaama/Documents/MARS-Firmware/LIAM/dev/simulator')
import physics
#import visualization

'''
start_lat = 40.7128  # Latitude of start point
start_lon = -74.0060  # Longitude of start point
end_lat = 34.0522  # Latitude of end point
end_lon = -118.2437  # Longitude of end point
num_points = 10  # Number of points in the generated path

path = generate_path(start_lat, start_lon, end_lat, end_lon, num_points)

print("Generated Path:")
for point in path:
    print(point)

plot_path(path)
'''

# Initial state
mass = 1000  # kg
initial_position = (0, 0, 0)  # (x, y, z) coordinates
initial_velocity = (10, 0, 0)  # (vx, vy, vz) velocities

# Time step and duration
dt = 0.1  # time step in seconds
duration = 5  # duration in seconds

# Simulation loop
num_steps = int(duration / dt)
position = initial_position
velocity = initial_velocity

for step in range(num_steps):
    # Update the plane's state
    position, velocity = physics.update_plane(mass, position, velocity, dt)

    # Get the new position from the updated state
    new_position = position

    # Print the new position
    print(f"Step {step+1}: New Position = {new_position}")

    # Optionally, perform other computations or actions based on the new position

    # You can also access the plane's other attributes such as velocity, acceleration, etc. if needed

    # Wait for the time step before proceeding to the next iteration
    # (useful if you want to simulate the time progression realistically)
    # You can remove this line if you want the simulation to run as fast as possible
    time.sleep(dt)