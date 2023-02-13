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

#include"controller_tasks.hpp"

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
    //Start Serial Communication
    //Serial.begin(9600);
    //Setup pins - SPI,sensors
    //SPI
    //pin_setup();
    //SPI.begin();
    //SENSORS

    //Rotate wing servos to default 


    REQUESTS *reqObj = new REQUESTS();
    interrupts();
    //attachInterrupt(digitalPinToInterrupt(0),reqObj -> dPassthroughInterrupt,HIGH);
    //attachInterrupt(digitalPinToInterrupt(0),reqObj -> controllerReceiveInterrupt,HIGH);
    delete reqObj;

}

void CONTROLLER_TASKS::_IDLE_(){
    //Controller does nothing
}

//Telemetry checks, peripheral checks
void CONTROLLER_TASKS::_PREP_(){
    DRONE_TASKS *obj = new DRONE_TASKS();
    if(prep != 1)
        
        //Delay 30 seconds for possible ground interrupt

        //CHECKS

        prep = 1;
    }else{
        //Do nothing.
        //Drone already prepped
    }
    delete obj;
}

void CONTROLLER_TASKS::_ARMED_(){
    
}

//For manual testing, implement bypass to respond to sensor and motor
//comms without additional processes.
//+1 Overload

//Bypass
//No function overloading possible so search SBC table to 
//determine if return or non-return peripheral !! needs attention !!
void CONTROLLER_TASKS::_bypass_(char* sbc_id){
    REQUESTS *ReqObj = new REQUESTS();
    if(sbc_id){
        //bypass
        //Open valve
        //ReqObj -> controllerRequest(sbc_id,1);
        //Close valve
        //ReqObj -> controllerRequest(sbc_id,0);
    }else{
        //Sensor bypass
        //Request sensor data
        double data = ReqObj -> controllerRequest(sbc_id,2);
        //transmit_telemetry(data);
    }
}
 //Sensor bypass

//CHange state to idle
uint8_t CONTROLLER_TASKS::SWITCH2IDLE(){
    //Change variable
    uint8_t change = 0;
    if(compareX(recieve_telemetry(),"IDLE")){
        change = 1;
    }
    return change;
}

//CHange state to prep
uint8_t CONTROLLER_TASKS::SWITCH2PREP(){
    //Change variable
    uint8_t change = 0;
    if(compareX(recieve_telemetry(),"PREP")){
        change = 1;
    }
    return change;
}

//CHange state to armed
uint8_t CONTROLLER_TASKS::SWITCH2ARMED(){
    //Change variable
    uint8_t change = 0;
    if(compareX(recieve_telemetry(),"ARMED")){
        change = 1;
    }
    return change;
}

//Change state to bypass
uint8_t CONTROLLER_TASKS::SWITCH2BYPASS(){
    //Change variable
    uint8_t change = 0;
    if(compareX(recieve_telemetry(),"BYPASS")){
        change = 1;
    }
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