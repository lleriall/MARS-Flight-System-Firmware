from trace import generate_path
from utility import plot_path
import matplotlib.pyplot as plt

start_lat = 40.7128  # Latitude of start point
start_lon = -74.0060  # Longitude of start point
end_lat = 34.0522  # Latitude of end point
end_lon = -118.2437  # Longitude of end point
num_points = 10  # Number of points in the generated path

path = generate_path(start_lat, start_lon, end_lat, end_lon, num_points)

print("Generated Path:")
for point in path:
    print(point)

plot_path()