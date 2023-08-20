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


#ifndef LOGTYPES_H_
#define LOGTYPES_H_

/* System includes */
#include<inttypes.h>
#include<stdio.h>
#include<time.h>
#include<iostream>

/* Logging levels with 1 being severe, and 3 being safe */
typedef enum
{
    DEFAULT = 0,
    LOG_ERROR = 1,
    LOG_WARNING = 2,
    LOG_INFO = 3
}Loglevel_t;

/* Different states the machine can be in */
typedef enum
{
    NEUTRAL = 4,
    STANDBY = 5,
    BYPASS = 6,
    ARMED = 7
}Log_Machine_State_t;


#endif /* LOGTYPES_H_ */