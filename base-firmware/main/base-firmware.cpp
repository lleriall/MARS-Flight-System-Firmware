#include <stdio.h>
#include"../components/Comms/_broadcast.h"
#include"../components/HALX/mg90s_servo.h"
#include"../components/PTAM/_ptam.h"
#include"../components/system/validateSensors.h"
#include"../components/system/_state.h"
#include"../components/system/sys_controller.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include<string>

#define DRONE_STATE 1

extern "C"{
    void app_main(void){
        // Wait for Wi-Fi to initialize
        vTaskDelay(pdMS_TO_TICKS(2000)); // Delay for 2 seconds
        //Initialize NVS
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
        }
        ESP_ERROR_CHECK(ret);

        BroadcastedServer server;
        server.wifi_init_softap();

        SharedMemory& sharedMemory = SharedMemory::getInstance();
        CONTROLLER_TASKS *CTobj = new CONTROLLER_TASKS();
        //Boot 
        CTobj -> _init_();
        STATE *change = new STATE();
        while(1){
            #if DRONE_STATE == 1 // STANDBY
            //FROM STANDBY PREP WE CAN EITHER SWITCH TO ARMED OR BYPASS
            CTobj -> _PREP_();
            if(change -> SWITCH2ARMED() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 2
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            if(change -> SWITCH2BYPASS() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 3
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            #endif

            #if DRONE_STATE == 2 // ARMED
            //FROM ARMED WE CAN EITHER SWITCH TO STANDY PREP OR BYPASS
            CTobj -> _ARMED_();
            if(change -> SWITCH2PREP() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 1
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            if(change -> SWITCH2BYPASS() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 3
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            #endif
            
            #if DRONE_STATE == 3 // BYPASS
            //FROM BYPASS WE CAN EITHER SWITCH TO STANDY PREP OR ARMED
            CTobj -> _bypass_(std::string("ID"));
            if(change -> SWITCH2PREP() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 1
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            if(change -> SWITCH2ARMED() == 1){
                #undef DRONE_STATE
                #define DRONE_STATE 2
                //Set a stategic delay so we dont trigger CPU1 watchdog timer
                vTaskDelay(1);
                continue;
            }
            #endif

        }
        delete change;
        delete CTobj;
    }
}