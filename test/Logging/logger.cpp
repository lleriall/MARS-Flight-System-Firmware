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

#include "../statemachine/_ptam.h"
#include "logger.hpp"
#include "esp_timer.h"


/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @return std::string
 */
std::string Logger::EVENT_LOG_SDD(void)
{
    /* Temporary timer start*/
    uint64_t start_time = esp_timer_get_time();
    SharedMemory &obj = SharedMemory::getInstance();

    /* Query ptam registers for required data */
    std::string ID = obj.getLastString("stateDescript");
    int state_data = obj.getLastInt("state");

    double FLS = obj.getLastDouble("WingFL");

    double FRS = obj.getLastDouble("WingFR");

    double RLS = obj.getLastDouble("WingRL");

    double RRS = obj.getLastDouble("WingRR");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = end_time - start_time;

    std::string log_ev = "LOG_SDD";

    // Build the formatted string combining format and data
    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tDATA: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tWING-FL-POS: " + std::to_string(FLS) + "\n";
    formatted_output += "\t\tWING-FR-POS: " + std::to_string(FRS) + "\n";
    formatted_output += "\t\tWING-RL-POS: " + std::to_string(RLS) + "\n";
    formatted_output += "\t\tWING-RR-POS: " + std::to_string(RRS) + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}



/**
 * @brief Queries all required ptam registers, formats them, logs them, and returns the log
 *
 * @return std::string
 */
std::string Logger::EVENT_LOG_SSL(void)
{
    /* Start temporary timer */
    uint64_t start_time = esp_timer_get_time();
    SharedMemory &obj = SharedMemory::getInstance();

    /* Query ptam registers */
    std::string state = obj.getLastString("stateDescript");
    std::string ID = "LOG_SSL_ID";

    int state_data = obj.getLastInt("state");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = start_time - end_time;

    /* Format and output data */
    std::string log_ev = "LOG_SSL";

    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tSTATE: " + state + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}



/**
 * @brief Called when an error rises. Formats data and logs it
 *
 * @param ID
 * @param exception_type
 * @param additional_info
 * @return std::string
 */
std::string Logger::EVENT_LOG_SEL(std::string ID, mars_exception_t::Type exception_type,
                                  std::string additional_info)
{
    /* Set temporary timer */
    uint64_t start_time = esp_timer_get_time();
    SharedMemory &obj = SharedMemory::getInstance();

    /* Get ptam data */
    int state_data = obj.getLastInt("state");

    uint64_t end_time = esp_timer_get_time();
    uint64_t elapsed_time = end_time - start_time;

    /* Check which routine fail occurred */
    std::string exceptionTypeStr;
    switch (exception_type)
    {
    case mars_exception_t::ROUTINE_SOFT_FAIL:
        exceptionTypeStr = "ROUTINE_SOFT_FAIL";
        break;
    case mars_exception_t::ROUTINE_HARD_FAIL:
        exceptionTypeStr = "ROUTINE_HARD_FAIL";
        break;
    default:
        exceptionTypeStr = "UNKNOWN";
        break;
    }
    /* Format and output the data */
    std::string log_ev = "LOG_SEL";

    std::string formatted_output;
    formatted_output += "\n\n" + log_ev + ":\n";
    formatted_output += "\t{\n";
    formatted_output += "\t\tID: " + ID + "\n";
    formatted_output += "\t\tTIME: " + std::to_string(elapsed_time) + "\n";
    formatted_output += "\t\tMACHINE-STATE: " + std::to_string(state_data) + "\n";
    formatted_output += "\t\tEXCEPTION-TYPE: " + std::to_string(exception_type) + "\n";
    formatted_output += "\t\tINFO: " + additional_info + "\n";
    formatted_output += "\t}\n\n";

    return formatted_output;
}
