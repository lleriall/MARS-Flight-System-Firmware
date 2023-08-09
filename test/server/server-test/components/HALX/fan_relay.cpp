#include"fan_relay.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define RELAY_GPIO_PIN gpio_num_t(17)

void FAN_COOLING::init_relay(){
    gpio_config_t io_conf;
    // Disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    // Set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    // Bit mask of the pins that you want to set
    io_conf.pin_bit_mask = (1ULL << RELAY_GPIO_PIN);
    // Disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    // Enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    // Configure the GPIO with the given settings
    gpio_config(&io_conf);
}

void FAN_COOLING::fan_relay_on(){
    gpio_set_level(RELAY_GPIO_PIN, 0);
}

void FAN_COOLING::fan_relay_off(){
    gpio_set_level(RELAY_GPIO_PIN, 1);
}

void FAN_COOLING::coolSierra_task(){
    int8_t sierraTemp = 24;
    //ESP_LOGI("Temp","FAN_FLAG: %d",sierraTemp);
    if(sierraTemp >= 20){
        fan_relay_on();
    }else{
        fan_relay_off();
    }
}

