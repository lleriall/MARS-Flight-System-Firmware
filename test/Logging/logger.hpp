/////////////////////////////////////////////////////////////////////////////
// Name:        logger.hpp
// Purpose:     Logger components
// Author:      Lukas Jackson
// Modified by:
// Created:     8/18/2023
// Copyright:   (c) 2023 limitless Aeronautics
// Licence:     Massachusetts Institute of Technology (MIT)
/////////////////////////////////////////////////////////////////////////////
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
    |    STANDBY   Vehicle IDLE Mode
    |    BYPASS    Motor and Sensors Interface
    |    ARMED     Ready for takeoff
    ==============================================
    */
    Log_Machine_State_t get_current_machine_state(Log_Machine_State_t machine_state);

    /* Sets the UAV current state

    ==============================================
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