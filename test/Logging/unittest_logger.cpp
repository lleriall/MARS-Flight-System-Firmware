/**
 * @file unittest_logger.cpp
 * @brief logger unit test
 *
 * Testing various functions from the logger.cpp translation unit to verify update functionality
 *
 *
 * @date August 18th 2023
 * @copyright Copyright (c) 2023 limitless Aeronautics
 *
 * @author Lukas Jackson
 *
 * @license MIT License
 *          Copyright (c) 2023 limitless Aeronautics
 *          Permission is hereby granted, free of charge, to any person obtaining a copy
 *          of this software and associated documentation files (the "Software"), to deal
 *          in the Software without restriction, including without limitation the rights
 *          to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *          copies of the Software, and to permit persons to whom the Software is
 *          furnished to do so, subject to the following conditions:
 *          The above copyright notice and this permission notice shall be included in all
 *          copies or substantial portions of the Software.
 *          THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *          IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *          FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *          AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *          LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *          OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *          SOFTWARE.
 */



/* System includes */


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

    const time_t curr_time = 0;

/* Log events */

/* Retrieve the current machine state */
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = STANDBY;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = BYPASS;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n";

    Machine = ARMED;
    log_results << "Current machine state: " << obj.get_current_machine_state(Machine) << "\n\n";

/* Set the machine state */
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_WARNING;
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n";

    level = LOG_ERROR;
    log_results << "Set current machine state: " << obj.set_current_machine_state(level) << "\n\n";

/* 8.19.23 Testing new log formatting */
    Logger::flight_data_t format_msg = {"UAV-UNIT", 1, curr_time, Machine};

    /* Logging format prototype */
    log_results
        << "\n\nNEW LOGGED EVENT: "
        <<"\n\t{\n\t\tID: " << format_msg.id
        << "\n\t\tTIME: " << format_msg.timestamp
        << "\n\t\tDATA: "<< format_msg.data
        << "\n\t\tMESSAGE: " << format_msg.m_state
        << "\n\t}";


    /* Created new flight data variable to distinguish unit tests from previous */
    time_t t_stamp = 4;
    Logger::flight_data_t format_msg2 = {"UAV-UNIT-23", 1, t_stamp, Machine};


    obj.create_log_message(format_msg2);
    log_results << "\n\nTimestamp: " << t_stamp;


    log_results << "\n\n\nThis file was generated from the unittest_logger.cpp file. ";

    log_results.close();

    return 0;
}