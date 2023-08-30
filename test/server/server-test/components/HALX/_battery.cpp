#include"_battery.h"
#include "driver/gpio.h"

//https://en.ovcharov.me/2020/02/29/how-to-measure-battery-level-with-esp32-microcontroller/

#define BATTERY_GPIO_PIN gpio_num_t(0)
#define R2 100
#define R3 10
#define VOLTAGE_OUT(Vin) (((Vin) * R3) / (R2 + R3))
#define VOLTAGE_MAX 4200
#define VOLTAGE_MIN 3300
#define ADC_REFERENCE 1100
#define VOLTAGE_TO_ADC(in) ((ADC_REFERENCE * (in)) / 4096)
#define BATTERY_MAX_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MAX))
#define BATTERY_MIN_ADC VOLTAGE_TO_ADC(VOLTAGE_OUT(VOLTAGE_MIN))

void BATTERY::batteryInterfaceInit(){
    gpio_config_t io_conf;
    //interrupt of rising edge
    io_conf.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins
    io_conf.pin_bit_mask = BATTERY_GPIO_PIN;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    // Configure the GPIO with the given settings
    gpio_config(&io_conf);
}

double BATTERY::returnBatteryVoltage(){

}

double BATTERY::returnBatteryCurrentDraw(){

}

double BATTERY::returnBatteryPercent(){
    int adc;
    int battery_percentage = 100 * (adc - BATTERY_MIN_ADC) / (BATTERY_MAX_ADC - BATTERY_MIN_ADC);

    if (battery_percentage < 0)
        battery_percentage = 0;
    if (battery_percentage > 100)
        battery_percentage = 100;

    return battery_percentage;
}