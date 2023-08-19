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


#ifndef LOGGER_HPP_
#define LOGGER_HPP_

/* System includes */
#include<type_traits>
#include<iostream>

/* Log includes */
#include"include/logtypes.h"

/* PTAM includes */
#include"../../base-firmware/components/PTAM/_ptam.h"

class Logger
{
public:
    ~Logger() {}

    /* Logs a system event
    ==============================================
    |   LOG_ERROR       Logging Error Level
    |   LOG_WARNING     Logging Warning Level
    |   LOG_INFO        Logging Information level
    ==============================================
    */
    Loglevel_t log_event(const std::string id,const int data);

    /* Returns the UAV current state
    ==============================================
    |    NEUTRAL   A Default State
    |    STANDBY   Vehicle IDLE Mode
    |    BYPASS    Motor and Sensors Interface
    |    ARMED     Ready for takeoff
    ==============================================
    */
    Log_Machine_State_t get_current_machine_state(Log_Machine_State_t machine_state);

    /* Sets the UAV current state
    ==============================================
    |    NEUTRAL   A Default State
    |    STANDBY   Vehicle IDLE Mode
    |    BYPASS    Motor and Sensors Interface
    |    ARMED     Ready for takeoff
    ==============================================
    */
    Log_Machine_State_t set_current_machine_state(Loglevel_t loglevel);

private:

    SharedMemory& sharedMemory = SharedMemory::getInstance();

    static Loglevel_t status;

    static Log_Machine_State_t machine_state;
};

#endif /* LOGGER_HPP_ */
