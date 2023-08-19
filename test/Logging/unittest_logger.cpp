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


/* System includes */
#include <iostream>
#include <fstream>

/* logger includes */
#include "logger.hpp"

Log_Machine_State_t Machine = NEUTRAL;

int main(void)
{
    /* Create log file to dump unit test results */
    std::ofstream log_results("Log_Results.txt");

    Logger obj; /* Create a logger object */
    Loglevel_t level = LOG_INFO; /* Set the level of the log */
    std::string ID = "UNIT_UAV"; /* Assign an ID to the log that will be stored */

/* Log events */
    log_results << "Logged event: " << obj.log_event(ID, 1) << "\n";
    log_results << "Logged event: " << obj.log_event("UNIT_UAV", 1) << "\n";

    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

/* Retrieve the current machine state */
    Machine = STANDBY;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = BYPASS;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = ARMED;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

/* Set the machine state */
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_WARNING;
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_ERROR;
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";


    log_results << "\n\n\n\nThis file was generated from the unittest_logger.cpp file. ";

    log_results.close();
    return 0;
}