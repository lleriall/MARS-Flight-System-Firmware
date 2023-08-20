/*MIT License
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
SOFTWARE.*/

/* PTAM includes */
#include"../statemachine/_ptam.h"

/* System includes */
#include <iostream>


SharedMemory& sharedMemory = SharedMemory::getInstance();
Loglevel_t Logger::status = DEFAULT;
Log_Machine_State_t Logger::machine_state = NEUTRAL;

Loglevel_t Logger::log_event(const std::string id, const int data)
{
    sharedMemory.storeInt(id, data);
    return status = LOG_INFO;
};

Loglevel_t Logger::log_event(const Logger::flight_data_t& flight_data )
{
    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}

Loglevel_t Logger::log_event(const Logger::flight_data_t flight_data, const Loglevel_t status_t)
{
    sharedMemory.storeMessage(flight_data);
    return status = status_t;
}

Logger::flight_data_t Logger::create_log_message(const std::string id, const int data, const time_t& timestamp, const Log_Machine_State_t& machine_state)
{
    Logger::flight_data_t log_message = {id, data, timestamp, machine_state};
    sharedMemory.storeMessage(log_message);
    return log_message;
}

Log_Machine_State_t Logger::get_current_machine_state(Log_Machine_State_t machine_state){ return machine_state;}

Log_Machine_State_t Logger::set_current_machine_state(Loglevel_t Loglevel){
    if(Loglevel == LOG_ERROR)
    {
        machine_state = STANDBY;
    }
    else if(Loglevel == LOG_WARNING)
    {
        machine_state = ARMED;
    }
    else if(Loglevel == LOG_INFO)
    {
        machine_state = ARMED;
    }
    else
        machine_state = STANDBY;

    return machine_state;
}
