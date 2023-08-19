/////////////////////////////////////////////////////////////////////////////
// Name:        unittest_logger.cpp
// Purpose:     logger unit test
// Author:      Lukas Jackson
// Modified by:
// Created:     8/18/2023
// Copyright:   (c) 2023 limitless Aeronautics
// Licence:     Massachusetts Institute of Technology (MIT)
/////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "logger.hpp"

Log_Machine_State_t Machine = NEUTRAL;

int main(void)
{

    Logger obj; /* Create a logger object */
    Loglevel_t level = LOG_INFO; /* Set the level of the log */
    std::string ID = "UNIT_UAV"; /* Assign an ID to the log that will be stored */

/* Log events */
    std::cout << "Logged event: " << obj.log_event(ID, 1) << "\n";
    std::cout << "Logged event: " << obj.log_event("UNIT_UAV", 1) << "\n";

    std::cout << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

/* Retrieve the current machine state */
    Machine = STANDBY;
    std::cout << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = BYPASS;
    std::cout << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = ARMED;
    std::cout << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

/* Set the machine state */

    std::cout << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_WARNING;
    std::cout << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_ERROR;
    std::cout << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    return 0;
}