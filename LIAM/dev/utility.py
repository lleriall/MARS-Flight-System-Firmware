'''
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
'''

import matplotlib.pyplot as plt

def plot_path(path):
    #Plots the given path of coordinates.
    latitudes = [point[0] for point in path]
    longitudes = [point[1] for point in path]

    plt.plot(longitudes, latitudes, 'bo-')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.title('Generated Path')
    plt.grid(True)
    plt.show()

def extractXY(points):
    extrctX = [point[0] for point in points]
    extrctY = [point[1] for point in points]
    extrctZ = [point[2] for point in points]
    return extrctX,extrctY,extrctZ

def get_last_value(points,variable):
    if len(points) == 0:
        return None
    if variable == 'x':
        last_point = points[-1]
        x, _, _ = last_point
        return x
    if variable == 'y':
        last_point = points[-1]
        _, y, _ = last_point
        return y
    if variable == 'z':
        last_point = points[-1]
        _, _, z = last_point
        return z
    return ValueError
    