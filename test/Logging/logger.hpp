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
#include<fstream>
#include<filesystem>

/* Log includes */
#include"include/logtypes.h"


class Logger
{
public:

    /* Flight data formatter
    ==============================================
    |   timestamp   Time log message is made
    |   m_state     Machine state during message
    ==============================================
    */
    typedef struct
    {
        std::string id;
        int data;
        const time_t timestamp;
        Log_Machine_State_t m_state;

        /* Add pressure functionality*/

        /* Add altitude functionality */

        /* Add speed functionality */

    }flight_data_t;

    /* Logs a system event
    ==============================================
    |   LOG_ERROR       Logging Error Level
    |   LOG_WARNING     Logging Warning Level
    |   LOG_INFO        Logging Information level
    ==============================================
    */
    Loglevel_t log_event(const std::string id,const int data);

    /* Takes flight_data_t reference */
    Loglevel_t log_event(const Logger::flight_data_t& flight_data);

    /* Takes both flight_data_t reference and Loglevel_t status to change */
    Loglevel_t log_event(const Logger::flight_data_t flight_data, Loglevel_t status);




    //____________________________________________________________
    /* Returns struct obj of flight_data_t
    ==============================================
    |   ID              Message ID String
    |   Data            Info to be Sent
    |   Timestamp       When message is Sent
    |   Log State       Machine's current State
    ==============================================
    */
    flight_data_t create_log_message(const std::string id, const int data, const time_t& timestamp, const Log_Machine_State_t& machine_state);

    /* Returns log level flag */
    Loglevel_t create_log_message(flight_data_t& flight_data);




    //____________________________________________________________
    /* Returns the UAV current state
    ==============================================
    |    NEUTRAL   A Default State
    |    STANDBY   Vehicle IDLE Mode
    |    BYPASS    Motor and Sensors Interface
    |    ARMED     Ready for takeoff
    ==============================================
    */
    Log_Machine_State_t get_current_machine_state(Log_Machine_State_t machine_state);

    //____________________________________________________________
    /* Sets the UAV current state
    ==============================================
    |    NEUTRAL   A Default State
    |    STANDBY   Vehicle IDLE Mode
    |    BYPASS    Motor and Sensors Interface
    |    ARMED     Ready for takeoff
    ==============================================
    */
    Log_Machine_State_t set_current_machine_state(Loglevel_t loglevel);




    /* Get the machine's current time */
    time_t get_timestamp() noexcept;
private:

    static Loglevel_t status;
    static Log_Machine_State_t machine_state;
};
#endif /* LOGGER_HPP_ */
