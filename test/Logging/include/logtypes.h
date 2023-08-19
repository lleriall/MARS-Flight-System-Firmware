/////////////////////////////////////////////////////////////////////////////
// Name:        logtypes.h
// Purpose:     types for the logger
// Author:      Lukas Jackson
// Modified by:
// Created:     8/18/2023
// Copyright:   (c) 2023 limitless Aeronautics
// Licence:     Massachusetts Institute of Technology (MIT)
/////////////////////////////////////////////////////////////////////////////
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