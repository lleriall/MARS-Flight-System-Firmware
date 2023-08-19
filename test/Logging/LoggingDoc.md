# Logging Subsystem API

This writeup describes the overall, and gives a rundown of the logging subsystem.
The logging subsystem will be a main component moving forward.
Various components inside the core will be accessing the API of the logger to pass off
generic messages, status updates, errors, and function results.


# logger.hpp

This file currently contains a class submodule that will be accessed by core components

### logger.hpp functions

> - log_event(const std::string id, const int data);

**log_event**

Stores the **Program Temporary Access Memory(PTAM)** ID, and data into a PTAM register.
The PTAM is how various subsystems can communicate without having to directly request each other.
This reduces access time by having the components access the data through the ID.

> - get_current_machine_state(Log_Machine_State_t machine_state);

**get_current_machine_state**

The state of the machine can be altered by various subsystems or by the user at a given command or event.
This function returns the machine's current state.

> - set_current_machine_state(Loglevel_t loglevel);

**set_current_machine_state**

Just like **get_current_machine_state**, **set_current_machine_state** provides an interface for users and subsystems to set the machine's state
after a given event from the system or user.




# logtypes.h

This file contains the types and values used in the logger. It can be included directly, or with the logger.hpp.

## Loglevel_t

Currently, this type returns 3 different values from the enumerated type:

**LOG_ERROR**

**LOG_WARNING**

**LOG_INFO**


Each enumerated value contains a value, with **LOG_ERROR** being 1, **LOG_WARNING** being 2, and **LOG_INFO** equalling 3.
Users can use these values to perform various tasks and run testing.
These values are not required to be used.

## Log_Machine_State_t

As of now, this type returns 4 values set at 4 through 7.
The device, or machine, can be set automatically, or manually using various states.

The machine can go through the following states:

**NEUTRAL**

**STANDBY**

**BYPASS**

**ARMED**




**NEUTRAL**

The NEUTRAL state is similar to the STANDBY state, but the difference is the lack of work being done
during the state.
This option is enabled by default when nothing is happing with the UAV.

**STANDBY**

The STANDBY state, similar to the NEUTRAL state, is responsible for maintaining general functions while the
UAV is active
This option is enabled when the drone is perfomring simple things such as updating, or testing mechanical components

**BYPASS**

During the BYPASS state, mechanical functionality of the drone is set, so various physical actions can take place such as testing and maintenance.
BYPASS enables the motors, sensors, and provides an interface via IP connection.

**ARMED**

The ARMED state is a completely autonomous state the drone is in. No control is entered by the user, hence why the state is referred to as ARMED.
During the ARMED state, it is recommended to stay away from the drone as it is operating without an operator.
