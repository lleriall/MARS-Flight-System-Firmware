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
#include "../statemachine/_ptam.h"

/* System includes */

Loglevel_t Logger::status = DEFAULT;
Log_Machine_State_t Logger::machine_state = NEUTRAL;

Loglevel_t Logger::log_event(const std::string id, const int data)
{
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    sharedMemory.storeInt(id, data);
    return status = LOG_INFO;
};

Loglevel_t Logger::log_event(const Logger::flight_data_t &flight_data)
{
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}

Loglevel_t Logger::log_event(const Logger::flight_data_t flight_data, const Loglevel_t status_t)
{
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    sharedMemory.storeMessage(flight_data);
    return status = status_t;
}

Logger::flight_data_t Logger::create_log_message(const std::string id, const int data, const time_t &timestamp, const Log_Machine_State_t &machine_state)
{
    // Verify that the file exists using <filesystem>
    SharedMemory &sharedMemory = SharedMemory::getInstance();
    Logger::flight_data_t log_message = {id, data, timestamp, machine_state};
    std::ofstream logFile("Logging_Results.txt");
    if (logFile.is_open())
    {

        logFile << "\nNEW LOGGED EVENT:" << std::endl;
        logFile << "\t{" << std::endl;
        logFile << "\t\tID: " << id << std::endl;
        logFile << "\t\tTIME: " << timestamp << std::endl;
        logFile << "\t\tDATA: " << data << std::endl;
        logFile << "\t\tMACHINE STATE: " << machine_state << std::endl;
        logFile << "\t}\n\n" << std::endl;

        logFile.close();
    }
    else
    {
        /* For now, we can only return the log message if the file cannot be opened since we can't print to the terminal */
        return log_message;
    }

    sharedMemory.storeMessage(log_message);
    return log_message;
}

Loglevel_t Logger::create_log_message(flight_data_t &flight_data)
{
    SharedMemory &sharedMemory = SharedMemory::getInstance();
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
        return status = LOG_ERROR;
    }

    sharedMemory.storeMessage(flight_data);
    return status = LOG_INFO;
}

Log_Machine_State_t Logger::get_current_machine_state(Log_Machine_State_t machine_state) { return machine_state; }

Log_Machine_State_t Logger::set_current_machine_state(Loglevel_t Loglevel)
{
    if (Loglevel == LOG_ERROR)
    {
        machine_state = STANDBY;
    }
    else if (Loglevel == LOG_WARNING)
    {
        machine_state = ARMED;
    }
    else if (Loglevel == LOG_INFO)
    {
        machine_state = ARMED;
    }
    else
        machine_state = STANDBY;

    return machine_state;
}

/* Getters for constructing log messages */


time_t Logger::get_timestamp() noexcept
{
    std::time_t currentTime;
    std::time(&currentTime);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&currentTime));

    return currentTime;
}

