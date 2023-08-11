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


//Setup pins based on config
void CONTROLLER_TASKS::pin_setup(){
   
}

//Start comms and attach RF interrupt 
//ATTACH PIN NUMBERS
void CONTROLLER_TASKS::_init_(){
    PTAM_REGISTER_SET();
    //Setup pins - SPI,sensors
    //pin_setup();

    //SENSORS
    /*DataStore *ptObject = new DataStore();

    SensorValidator *valD = new SensorValidator();
    bool GPScheck = valD.validateGPSData();
    if(GPScheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "GPScheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }

    bool IMUcheck = valD.validateIMUData();
    if(IMUcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "IMUcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }

    bool BMPcheck = valD.validateBMP280Data();
    if(BMPcheck == true){
        //Update PTAM Register = 1 denoting sensor success
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,1);
    }else{
        //Update PTAM Register = 0 denoting sensor fail
        std::string reg_name = "BMPcheck";
        //Remove previous value
        ptObject.clearData(reg_name);
        //Push Update
        ptObject.storeData(reg_name,0);
    }*/
    //SETUP ONBOARD DISPLAY
   // _ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    //dispInit._init_();
    //dispInit._showBoot();
    //delete dispInit;
}

void CONTROLLER_TASKS::_IDLE_(){
    //Controller does nothing
}

//Telemetry checks, peripheral checks
void CONTROLLER_TASKS::_PREP_(){
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    auto lat = sharedMemory.getLastDouble("TLat");
    //ESP_LOGI("LAT", "%f",lat);
}

void CONTROLLER_TASKS::_ARMED_(){
    //_ONBOARD_DISPLAY *dispInit = new  _ONBOARD_DISPLAY();
    //dispInit.stateARMED();
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
void CONTROLLER_TASKS::_bypass_(std::string sbc_id){
    //Check if there is any update to the ptam registers
    SharedMemory& sharedMemory = SharedMemory::getInstance();
    //If there is a difference between Wing Register and referenceupdate register there has been an update
    auto dtaWFL = sharedMemory.getLastDouble("WingFL");
    auto dtaWFR = sharedMemory.getLastDouble("WingFR");
    auto dtaWRL = sharedMemory.getLastDouble("WingRL");
    auto dtaWRR = sharedMemory.getLastDouble("WingRR");

    auto dtaWFL_ref = sharedMemory.getLastDouble("FL-ref-byp");
    auto dtaWFR_ref = sharedMemory.getLastDouble("FR-ref-byp");
    auto dtaWRL_ref = sharedMemory.getLastDouble("RL-ref-byp");
    auto dtaWRR_ref = sharedMemory.getLastDouble("RR-ref-byp");

    ESP_LOGI("SEN", "FL %f",dtaWFL);
    ESP_LOGI("SEN", "FL-ref %f",dtaWFL_ref);

    WingTranslate *obj = new WingTranslate();
    if(dtaWFL != dtaWFL_ref){
        //There has been an update, wings can be commanded
        obj -> mcpwm_servo_control(dtaWFL,0,SPEED_FAST);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("FL-ref-byp");
        sharedMemory.storeDouble("FL-ref-byp", dtaWFL);
    }
    if(dtaWFR != dtaWFR_ref){
        //There has been an update, wings can be commanded
        obj -> mcpwm_servo_control(dtaWFR,1,SPEED_FAST);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("FR-ref-byp");
        sharedMemory.storeDouble("FR-ref-byp", dtaWFR);
    }
    if(dtaWRL != dtaWRL_ref){
        //There has been an update, wings can be commanded
        obj -> mcpwm_servo_control(dtaWRL,2,SPEED_FAST);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("RL-ref-byp");
        sharedMemory.storeDouble("RL-ref-byp", dtaWRL);
    }
    if(dtaWRR != dtaWRR_ref){
        //There has been an update, wings can be commanded
        obj -> mcpwm_servo_control(dtaWRR,3,SPEED_FAST);
        //Update the reference register
        //Clear previous register to avoid memory overflow
        sharedMemory.clearData("RR-ref-byp");
        sharedMemory.storeDouble("RR-ref-byp", dtaWRR);
    }
    delete obj;
}
 //Sensor bypass

void CONTROLLER_TASKS::PTAM_REGISTER_SET(){
    //On startup init PTAM registers so no module calls an undefined register
    //StateMachine main status | Init to STANDBY PREP ON INIT
    // Store data in shared memory
    SharedMemory& sharedMemory = SharedMemory::getInstance();

    sharedMemory.storeInt("state", 1);
    sharedMemory.storeString("stateDescript", "PREP");
    //GPS functionality flag
    sharedMemory.storeInt("GPScheck", 0);
    //IMU functionality flag
    sharedMemory.storeInt("IMUcheck", 0);
    //BMP functionality flag
    sharedMemory.storeInt("BMPcheck", 0);
    //ServerSetupFlag
    sharedMemory.storeInt("setupSFlag", 0);
    //Target Latitude 
    sharedMemory.storeDouble("TLat", 0);
    //Target Longitude
    sharedMemory.storeDouble("TLong", 0);
    //Target Altitude
    sharedMemory.storeDouble("TAlt", 0);
    //Cruise Altitude
    sharedMemory.storeDouble("CAlt", 0);
    //Target Velocity
    sharedMemory.storeDouble("TVel", 0);
    //Wing FL
    sharedMemory.storeDouble("WingFL", 0);
    sharedMemory.storeDouble("FL-ref-byp", 0);
    //Wing FR
    sharedMemory.storeDouble("WingFR", 0);
    sharedMemory.storeDouble("FR-ref-byp", 0);
    //Wing RL
    sharedMemory.storeDouble("WingRL", 0);
    sharedMemory.storeDouble("RL-ref-byp", 0);
    //Wing RR
    sharedMemory.storeDouble("WingRR", 0);
    sharedMemory.storeDouble("RR-ref-byp", 0);
    //Throttle
    sharedMemory.storeDouble("THR", 0);
    sharedMemory.storeDouble("THR-ref-byp", 0);

    //auto po = init.getStringData(std::string("stateDescript")).back();
    //std::cout << po << std::endl;
}

