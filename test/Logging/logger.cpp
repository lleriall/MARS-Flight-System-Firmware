/////////////////////////////////////////////////////////////////////////////
// Name:        logger.cpp
// Purpose:     Main MARS Logger
// Author:      Lukas Jackson
// Modified by:
// Created:     8/18/2023
// Copyright:   (c) [2023] Lukas Jackson
// Licence:     Massachusetts Institute of Technology (MIT)
/////////////////////////////////////////////////////////////////////////////


/* Logger includes */
#include "logger.hpp"
#include <iostream>

Loglevel_t Logger::status;
Log_Machine_State_t Logger::machine_state = NEUTRAL;



Loglevel_t Logger::log_event(const std::string id, const int data)
{
    sharedMemory.storeInt(id, data);
    return status = LOG_INFO;
};

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