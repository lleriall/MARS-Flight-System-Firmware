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
import math

def calculate_coordinate(lat1, lon1, lat2, lon2, distance):
    """
    Calculates a new coordinate given a starting coordinate, distance, and bearing.
    """
    radius = 6371  # Radius of the Earth in kilometers
    brng = math.radians(distance / radius)  # Convert distance to radians

    lat1 = math.radians(lat1)
    lon1 = math.radians(lon1)

    lat2 = math.asin(math.sin(lat1) * math.cos(brng) +
                     math.cos(lat1) * math.sin(brng) * math.cos(lat2))
    lon2 = lon1 + math.atan2(math.sin(brng) * math.sin(lat2) * math.cos(lat1),
                             math.cos(brng) - math.sin(lat1) * math.sin(lat2))

    return math.degrees(lat2), math.degrees(lon2)

def generate_path(start_lat, start_lon, end_lat, end_lon, num_points):
    """
    Generates a path of coordinates between two given latitude and longitude points.
    """
    delta_lat = (end_lat - start_lat) / num_points
    delta_lon = (end_lon - start_lon) / num_points

    path = [(start_lat + i * delta_lat, start_lon + i * delta_lon) for i in range(num_points + 1)]

    return path