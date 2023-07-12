import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

def visualize_trajectory(x, y, z):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Altitude')

    # Set the aspect ratio and limits
    ax.set_box_aspect([1, 1, 0.5])
    ax.set_xlim(min(x), max(x))
    ax.set_ylim(min(y), max(y))
    ax.set_zlim(min(z), max(z))

    # Create initial empty lines for the animation
    line, = ax.plot([], [], [], marker='o', label='Trajectory')
    current_point, = ax.plot([], [], [], 'ro', label='Current Position')

    # Function called for each frame of the animation
    def update(frame):
        # Update the trajectory line
        line.set_data(x[:frame+1], y[:frame+1])
        line.set_3d_properties(z[:frame+1])

        # Update the current position
        current_position = [x[frame], y[frame], z[frame]]
        current_point.set_data([current_position[0]], [current_position[1]])
        current_point.set_3d_properties([current_position[2]])

        return line, current_point

    # Create the animation
    anim = FuncAnimation(fig, update, frames=len(x), interval=200, blit=True)

    # Display the animation
    plt.legend()
    plt.show()

def simulate_flight(start_position, end_position, num_steps):
    # Generate a trajectory
    x = [start_position[0]]
    y = [start_position[1]]
    z = [start_position[2]]
    for _ in range(num_steps):
        # Calculate the new position based on your physics model
        # Replace the following line with your own physics calculations
        new_position = [x[-1] + 1, y[-1] + 1, z[-1] + 1]
        x.append(new_position[0])
        y.append(new_position[1])
        z.append(new_position[2])

    # Visualize the trajectory animation
    visualize_trajectory(x, y, z)

start_position = [10, 0, 0]
end_position = [10, 15, 20]
num_steps = 20
simulate_flight(start_position, end_position, num_steps)