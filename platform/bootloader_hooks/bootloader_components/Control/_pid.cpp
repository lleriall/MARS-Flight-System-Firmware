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

#include"_pid.h"

uint8_t tagCount, PR_count;
double PID_PR[64][5];
//char *tags = (char*)malloc(12);
char* tags[64];

//Important for PID process identification
double kp = 0.5,ki = 0.2,kd = 0.1;
double error_previous = 0,error_integral = 0;

double error,processVar;
double derivative,proportional,integral;

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getProportional(){
    proportional = kp * error;
    return proportional;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getIntegral(){
    integral = ki * error_integral;
    return integral;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::getDerivative(){
    derivative = kd * derivative;
    return derivative;
}

double PROPORTIONAL_INTEGRAL_DERIVATIVE::PID_MAIN(char* Process,double current,double setpoint){
    updateConstants(Process);
    processVar = current;
	error = setpoint - processVar;
	error_integral += error * dt;
    derivative = (error - error_previous) / dt;
    error_previous = error;
    double dv = getDerivative();
    double it = getIntegral();
    double prop = getProportional();
    auto result = proportional + integral + derivative;
    return result;
}

void PROPORTIONAL_INTEGRAL_DERIVATIVE::createPIDinstance(char* tag,double kp,double ki,double kd){ 
    if(!checkforInstance(tag)){
        tags[tagCount] = tag;
        tagCount++;
        PID_PR[PR_count][0] = kp;
        PID_PR[PR_count][1] = ki;
        PID_PR[PR_count][2] = kd;
        //Create error variables
        double erPrev = 0,erInteg = 0;
        PID_PR[PR_count][3] = erPrev;
        PID_PR[PR_count][4] = erInteg;
        PR_count++;
    }else{
        //Do nothing
    }
    
}

void PROPORTIONAL_INTEGRAL_DERIVATIVE::updateConstants(char* Process){
    uint8_t index = -1;
    for(size_t i = 0; i < tagCount;i++){
        if(strcmp(tags[i],Process)){
            index = i;
        }
    }
    //ErrorDump sen;
    if(index != -1){
        kp = PID_PR[index][0];
        ki = PID_PR[index][1];
        kd = PID_PR[index][2];
        error_previous = PID_PR[index][3];
        error_integral = PID_PR[index][4];
   }else{
       //sen.ERROR_DUMP("311");
   }
}

bool PROPORTIONAL_INTEGRAL_DERIVATIVE::compare(char* x, char* y){
    if (x != y){
        return false;
    }
    else{
        return true;
    }
}

bool PROPORTIONAL_INTEGRAL_DERIVATIVE::checkforInstance(char* tag){
    bool instanceTrue = false;
    for(size_t i = 0; i < tagCount;i++){
        if(strcmp(tag,tags[i])){
            instanceTrue = true;
        }
    }
    return instanceTrue;
}