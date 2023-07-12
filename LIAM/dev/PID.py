def calculate_error(target, current):
    return [target[i] - current[i] for i in range(len(target))]

def calculate_integral(integral, errors, dt):
    if isinstance(integral, list):
        return [integral[i] + errors[i] * dt for i in range(len(integral))]
    else:
        return integral + errors * dt
    
def calculate_derivative(previous_error, error, dt):
    return (error - previous_error) / dt

def calculate_control_signal(kp, ki, kd, error, integral, derivative):
    return kp * error + ki * integral + kd * derivative

def pid_controller(target, current, kp, ki, kd, integral, previous_errors, dt):
    errors = calculate_error(target, current)
    integrals = [calculate_integral(integral[i], errors[i], dt) for i in range(3)]
    derivatives = [calculate_derivative(previous_errors[i], errors[i], dt) for i in range(3)]

    control_signals = [
        calculate_control_signal(kp, ki, kd, errors[i], integrals[i], derivatives[i])
        for i in range(3)
    ]

    return control_signals