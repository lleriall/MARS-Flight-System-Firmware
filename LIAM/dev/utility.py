import matplotlib.pyplot as plt

def plot_path(path):
    """
    Plots the given path of coordinates.
    """
    latitudes = [point[0] for point in path]
    longitudes = [point[1] for point in path]

    plt.plot(longitudes, latitudes, 'bo-')
    plt.xlabel('Longitude')
    plt.ylabel('Latitude')
    plt.title('Generated Path')
    plt.grid(True)
    plt.show()