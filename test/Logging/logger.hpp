/**
 * @file logger.hpp
 * @brief API toolkit for logger
 *
 * This file provides the necessary prototypes for functions that will be
 * defined in the translation unit.
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


#ifndef LOGGER_HPP_
#define LOGGER_HPP_

/* System includes */
#include<fstream>

/* Log includes */
#include"include/logtypes.h"


class Logger
{
public:


    /**
     * @brief type struct
     *
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


    /**
     * @brief
     * 
     * @param id 
     * @param data
     */
    void log_event(const std::string id,const int data);


    /**
     * @brief
     * 
     * @param flight_data
     */
    void log_event(const Logger::flight_data_t& flight_data);


    /**
     * @brief Create a log message object
     * 
     * @param flight_data 
     * @return Loglevel_t
     */
    void create_log_message(flight_data_t& flight_data);


    /**
     * @brief Get the current machine state object
     * 
     * @param machine_state 
     * @return Log_Machine_State_t 
     */
    Log_Machine_State_t get_current_machine_state(Log_Machine_State_t machine_state);


    /**
     * @brief Set the current machine state object
     *
     * @param loglevel
     * @return Log_Machine_State_t
     */
    Log_Machine_State_t set_current_machine_state(Loglevel_t loglevel);


    /* Get the machine's current time */
    time_t get_timestamp() noexcept;

private:

    static Loglevel_t status;
    static Log_Machine_State_t machine_state;
};
#endif /* LOGGER_HPP_ */
