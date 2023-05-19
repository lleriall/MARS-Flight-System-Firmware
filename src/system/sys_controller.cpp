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

#include"sys_controller.h"

//Variable noting whether engine has already been prepped
uint8_t prep;
//Variable noting whether engine has been started
uint8_t droneStarted;

//Setup pins based on config
void CONTROLLER_TASKS::pin_setup(){
    //Setup MASTER connection for forward neighbor
    //Set SlaveSelection pin as output.
    //uint8_t SlaveSelection = 0; //TEMP
    //pinMode(SlaveSelection, OUTPUT);
    //and Make it HIGH to prevent to start communication right away
    //digitalWrite(SlaveSelection, HIGH);

    //Setup SLAVE connection for backwards neighbor
}

//Setup comms to GSE over ESP32 Wifi
void CONTROLLER_TASKS::GSE_comms_setup(){


}
//Start comms and attach RF interrupt 
//ATTACH PIN NUMBERS
void CONTROLLER_TASKS::_init_(){
    //SET PID PROCESSES
    PROPORTIONAL_INTEGRAL_DERIVATIVE *_pobj = new PROPORTIONAL_INTEGRAL_DERIVATIVE();
    //ROLL RIGHT
    _pobj -> createPIDinstance("rollRight",0,0,0); //<- Gains
    //ROLL LEFT
    _pobj -> createPIDinstance("rollLeft",0,0,0);
    //PITCH UP
    _pobj -> createPIDinstance("pitchUp",0,0,0);
    //PITCH DOWN
    _pobj -> createPIDinstance("pitchDown",0,0,0);
    delete _pobj;
    //Start Serial Communication
    Serial.begin(9600);
    //Setup pins - SPI,sensors
    //pin_setup();
    //SPI.begin();
    //SENSORS

    //Rotate wing servos to default
    uint8_t defaultP = 0;
    _motors *_mObj = new _motors();
    _mObj -> adjustServoFWLEFT(defaultP);
    _mObj -> adjustServoFWRIGHT(defaultP);
    _mObj -> adjustServoRWLEFT(defaultP);
    _mObj -> adjustServoRWRIGHT(defaultP);
    delete _mObj;
}

void CONTROLLER_TASKS::_IDLE_(){
    //Controller does nothing
}

//Telemetry checks, peripheral checks
void CONTROLLER_TASKS::_PREP_(){

    if(prep != 1){
        
        //Delay 30 seconds for possible ground interrupt

        //CHECKS

        prep = 1;
    }else{
        //Do nothing.
        //Drone already prepped
    }
    //delete obj;
}

void CONTROLLER_TASKS::_ARMED_(){
    //Check if takeoff conditions met

    // If takeoff = true , Set cruise - follow waypoint

    //
}

//For manual testing, implement bypass to respond to sensor and motor
//comms without additional processes.
//+1 Overload

//Bypass
//No function overloading possible so search SBC table to 
//determine if return or non-return peripheral !! needs attention !!
void CONTROLLER_TASKS::_bypass_(char* sbc_id){
    if(sbc_id){
        //bypass
        
    }else{
        //Sensor bypass
        //Request sensor data
        //
    }
}
 //Sensor bypass

//CHange state to idle
uint8_t CONTROLLER_TASKS::SWITCH2IDLE(){
    _telemetry *tObj = new _telemetry();
    //Change variable
    uint8_t change = 0;
    if(compareX(tObj -> getLastRequest(),"IDLE")){
        change = 1;
    }
    delete tObj;
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),0);
    delete ptObject;
    return change;
}

//CHange state to prep
uint8_t CONTROLLER_TASKS::SWITCH2PREP(){
    _telemetry *tObj = new _telemetry();
    //Change variable
    uint8_t change = 0;
    if(compareX(tObj -> getLastRequest(),"PREP")){
        change = 1;
    }
    delete tObj;
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),1);
    delete ptObject;
    return change;
}

//CHange state to armed
uint8_t CONTROLLER_TASKS::SWITCH2ARMED(){
    _telemetry *tObj = new _telemetry();
    //Change variable
    uint8_t change = 0;
    if(compareX(tObj -> getLastRequest(),"ARMED")){
        change = 1;
    }
    delete tObj;
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),2);
    delete ptObject;
    return change;
}

//Change state to bypass
uint8_t CONTROLLER_TASKS::SWITCH2BYPASS(){
    _telemetry *tObj = new _telemetry();
    //Change variable
    uint8_t change = 0;
    if(compareX(tObj -> getLastRequest(),"BYPASS")){
        change = 1;
    }
    delete tObj;
    DataStore *ptObject = new DataStore();
    ptObject -> storeData(std::string("state"),3);
    delete ptObject;
    return change;
}

//Reset all drone tags
void CONTROLLER_TASKS::reset_(){
    //Reset prep tag
    prep = 0;

    //Reset drone started tag
    droneStarted = 0;
}

//If output = 1, strings match
uint8_t CONTROLLER_TASKS::compareX(char* x, char* y){
    if (x != y){
        return 0;
    }
    else{
        return 1;
    }
}