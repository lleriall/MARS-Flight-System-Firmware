/**
 * @file logger.cpp
 * @brief Logger API
 *
 * Functions defined from logger.hpp prototypes
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


/* PTAM includes */
#include "../PTAM/_ptam.h"

//  remove fstream usage
//  clean registers
//  remove global machine and status usage
//  use proper ptam<DONE>
//  interface to ptam<DONE>
//  fix includes<DONE>
//  update docs<DONE>


/* System includes */

Loglevel_t Logger::status = DEFAULT;
Log_Machine_State_t Logger::machine_state = NEUTRAL;

void Logger::log_event(const std::string id, const int data)
{
    DataStore *obj = new DataStore();
    obj->storeData(id, data);
};

void Logger::log_event(const Logger::flight_data_t &flight_data)
{
    DataStore *obj = new DataStore();
    obj->storeData(flight_data);
}

void Logger::create_log_message(flight_data_t &flight_data)
{
    DataStore *obj = new DataStore();
    std::ofstream logFile("Logging_Results.txt");
    if (logFile.is_open())
    {
        logFile << "\nLOG EVENT:" << std::endl;
        logFile << "\t{" << std::endl;
        logFile << "\t\tID: " << flight_data.id << std::endl;
        logFile << "\t\tTIME: " << flight_data.timestamp << std::endl;
        logFile << "\t\tDATA: " << flight_data.data << std::endl;
        logFile << "\t\tMACHINE STATE: " << machine_state << std::endl;
        logFile << "\t}\n\n" << std::endl;

        logFile.close();
    }
    else
    {
        return;
    }
    obj->storeData(flight_data);
    return;
}

Log_Machine_State_t Logger::get_current_machine_state(Log_Machine_State_t machine_state) { return machine_state; }

Log_Machine_State_t Logger::set_current_machine_state(Loglevel_t logLevel) {
    switch (logLevel) {
        case LOG_ERROR:
            machine_state = STANDBY;
            break;
        case LOG_WARNING:
        case LOG_INFO:
            machine_state = ARMED;
            break;
        default:
            machine_state = STANDBY;
            break;
    }

    return machine_state;
}
