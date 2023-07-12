def calculate_acceleration(mass, total_force):
    acceleration = (
        total_force[0] / mass,
        total_force[1] / mass,
        total_force[2] / mass
    )
    return acceleration

def calculate_total_force(thrust, drag, lift, gravity):
    total_force = (
        thrust,
        drag,
        lift - gravity
    )
    return total_force

def calculate_thrust():
    return (1000, 0, 0)

def calculate_drag(velocity):
    return (-0.1 * velocity[0], -0.1 * velocity[1], -0.1 * velocity[2])

def calculate_lift():
    return (0, 0, 0)

def calculate_gravity(mass):
    return (0, 0, 9.81 * mass)

def update_velocity(velocity, acceleration, dt):
    new_velocity = (
        velocity[0] + acceleration[0] * dt,
        velocity[1] + acceleration[1] * dt,
        velocity[2] + acceleration[2] * dt
    )
    return new_velocity

def update_position(position, velocity, dt):
    new_position = (
        position[0] + velocity[0] * dt,
        position[1] + velocity[1] * dt,
        position[2] + velocity[2] * dt
    )
    return new_position

def update_plane(mass, position, velocity, dt):
    thrust = calculate_thrust()
    drag = calculate_drag(velocity)
    lift = calculate_lift()
    gravity = calculate_gravity(mass)

    total_force = calculate_total_force(thrust, drag, lift, gravity)
    acceleration = calculate_acceleration(mass, total_force)
    new_velocity = update_velocity(velocity, acceleration, dt)
    new_position = update_position(position, new_velocity, dt)

    return new_position, new_velocity