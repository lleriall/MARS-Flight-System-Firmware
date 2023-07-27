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

#include <stdio.h>
#include<iostream>
#include<string>
#include"../bootloader_components/PTAM/_ptam.h"
#include"../bootloader_components/system/validateSensors.h"
#include"../bootloader_components/Control/_pid.h"

extern "C"{
    uint8_t SWITCH2IDLE();

    uint8_t SWITCH2PREP();

    uint8_t SWITCH2ARMED();

    uint8_t SWITCH2BYPASS();

    void ASSIGN_PREP_TASKS();

    void UNDEF_FLAGS(std::string state);

    void reset_();

    uint8_t compareX(std::string x, std::string y);

    std::string getLastStateRequest();

    void setInit();

    //Setup NodeMCU wifi comms
    void GSE_COMMS_SETUP();

    //Start comms and attach interrupts 
    void _init_();

    void _IDLE_();

    //Telemetry checks, peripheral checks
    void _PREP_();

    void _ARMED_();

    //For manual testing, implement bypass to respond to sensor and valve
    //comms without additional processes.
    //+1 Overload
    void _bypass_(char* sbc_id);

    //Setup Pins
    void pin_setup();

    //Reset all tags
    void reset_();

    void PTAM_REGISTER_SET();
}

extern "C"{
    void app_main(void){
        while(1){
            #if DRONE_STATE == 0 // IDLE
            _IDLE_();
            if(SWITCH2PREP() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 1
            }
            #endif

            #if DRONE_STATE == 1 // PREP
             _PREP_();
            if(SWITCH2ARMED() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 2
            }
            #endif

            #if DRONE_STATE == 2 // ARMED
            _ARMED_();
            if(SWITCH2IDLE() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 0
            }
            #endif
            
            #if DRONE_STATE == 3 // BYPASS
            _bypass_();
            #endif

        }
    
    }

}

extern "C"{
    //CHange state to idle
    uint8_t SWITCH2IDLE(){
        //Change variable
        uint8_t change = 0;
        if(compareX(getLastStateRequest(),"IDLE")){
            change = 1;
        }
        DataStore *ptObject = new DataStore();
        ptObject -> storeData(std::string("state"),0);
        delete ptObject;
        return change;
    }

    //CHange state to prep
    uint8_t SWITCH2PREP(){
        //Change variable
        uint8_t change = 0;
        if(compareX(getLastStateRequest(),std::string("PREP"))){
            change = 1;
        }
        DataStore *ptObject = new DataStore();
        ptObject -> storeData(std::string("state"),1);
        delete ptObject;
        return change;
    }

    //CHange state to armed
    uint8_t SWITCH2ARMED(){
        //Change variable
        uint8_t change = 0;
        if(compareX(getLastStateRequest(),std::string("ARMED"))){
            change = 1;
        }
        DataStore *ptObject = new DataStore();
        ptObject -> storeData(std::string("state"),2);
        delete ptObject;
        return change;
    }

    //Change state to bypass
    uint8_t SWITCH2BYPASS(){
        //Change variable
        uint8_t change = 0;
        if(compareX(getLastStateRequest(),std::string("BYPASS"))){
            change = 1;
        }
        DataStore *ptObject = new DataStore();
        ptObject -> storeData(std::string("state"),3);
        delete ptObject;
        return change;
    }

    void ASSIGN_PREP_TASKS(){
        DataStore *tsK = new DataStore();
        auto setupFL = tsK -> getIntData("TARGET-LAT").back();
        if(setupFL == 0){
            //
        }
    }

    void UNDEF_FLAGS(std::string state){
        DataStore* obj = new DataStore();
        if(state == "IDLE"){
            
        }
        if(state == "PREP"){
            //Reset drone server setup PTAM Register
            std::string reg_name = "setupSFlag";
            //Remove previous value
            obj -> clearData(reg_name);
            //Push Update
            obj -> storeData(reg_name,1);
        }
        if(state == "ARMED"){
        
        }
        if(state == "BYPASS"){
        
        }
        delete obj;
    }

    std::string getLastStateRequest(){
        //Get STATE data from PTAM
        DataStore* obj = new DataStore();
        std::vector<std::string> stringData = obj->getStringData("stateDescript");
        for (const std::string& element : stringData) {
            std::cout << element << std::endl;
        }
        auto dta = obj -> getStringData("stateDescript").back();
        delete obj;
        return dta; //REVIEW
    }

    //Reset all drone tags
    void reset_(){
        //Reset prep tag
        //prep = 0;

        //Reset drone started tag
        //droneStarted = 0;
    }

    //If output = 1, strings match
    uint8_t compareX(std::string x, std::string y){
        if (x != y){
            return 0;
        }
        else{
            return 1;
        }
    }

    //Setup pins based on config
    void pin_setup(){
    
    }

    //Setup comms to GSE over ESP32 Wifi
    void GSE_COMMS_SETUP(){
        // Initialize and start the server
        //server.begin();
        //server.sendWebpage();
        //server.handleNotFound();


    }
    //Start comms and attach RF interrupt 
    //ATTACH PIN NUMBERS
    void _init_(){
        PTAM_REGISTER_SET();
        //Setup pins - SPI,sensors
        //pin_setup();

        //SENSORS
        DataStore *ptObject = new DataStore();

        SensorValidator *valD = new SensorValidator();
        bool GPScheck = valD -> validateGPSData();
        if(GPScheck == true){
            //Update PTAM Register = 1 denoting sensor success
            std::string reg_name = "GPScheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,1);
        }else{
            //Update PTAM Register = 0 denoting sensor fail
            std::string reg_name = "GPScheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,0);
        }

        bool IMUcheck = valD -> validateIMUData();
        if(IMUcheck == true){
            //Update PTAM Register = 1 denoting sensor success
            std::string reg_name = "IMUcheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,1);
        }else{
            //Update PTAM Register = 0 denoting sensor fail
            std::string reg_name = "IMUcheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,0);
        }

        bool BMPcheck = valD -> validateBMP280Data();
        if(BMPcheck == true){
            //Update PTAM Register = 1 denoting sensor success
            std::string reg_name = "BMPcheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,1);
        }else{
            //Update PTAM Register = 0 denoting sensor fail
            std::string reg_name = "BMPcheck";
            //Remove previous value
            ptObject -> clearData(reg_name);
            //Push Update
            ptObject -> storeData(reg_name,0);
        }
        //SETUP ONBOARD DISPLAY
        //_ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
        //dispInit -> _init_();
        //dispInit -> _showBoot();
        //delete dispInit;
        //Rotate wing servos to default
        /*uint8_t defaultP = 0;
        _motors *_mObj = new _motors();
        _mObj -> adjustServoFWLEFT(defaultP);
        _mObj -> adjustServoFWRIGHT(defaultP);
        _mObj -> adjustServoRWLEFT(defaultP);
        _mObj -> adjustServoRWRIGHT(defaultP);
        delete _mObj;*/
    }

    void _IDLE_(){
        //Controller does nothing
    }

    //Telemetry checks, peripheral checks
    void _PREP_(){
        DataStore* obj = new DataStore();
        auto setupFL = obj -> getIntData("setupSFlag").back();
        if(setupFL == 0){
            GSE_COMMS_SETUP();
            //Set server setup PTAM register to 1
            obj -> clearData("setupSFlag");
            obj -> storeData(std::string("setupSFlag"),1);
        }
        //Controller runs ground server
        //server.handleClient();
        delete obj;
    }

    void _ARMED_(){
        //_ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
        //dispInit -> stateARMED();
        //delete dispInit;
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
    void _bypass_(char* sbc_id){
        //_ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
        //dispInit -> stateBYPASS();
        //delete dispInit;
        if(sbc_id){
            //bypass
            
        }else{
            //Sensor bypass
            //Request sensor data
            //
        }
    }
    //Sensor bypass

    void PTAM_REGISTER_SET(){
        //On startup init PTAM registers so no module calls an undefined register
        DataStore *init = new DataStore();
        //StateMachine main status
        init -> storeData("state"," ");
        //GPS functionality flag
        init -> storeData("GPScheck",0);
        //IMU functionality flag
        init -> storeData("IMUcheck",0);
        //BMP functionality flag
        init -> storeData("BMPcheck",0);
        //ServerSetupFlag
        init -> storeData("setupSFlag",0);
        delete init;
    }
}
