#include"_barometerEntry.h"
#include"bmp280.h"

static gpio_num_t i2c_gpio_sda = GPIO_NUM_21;
static gpio_num_t i2c_gpio_scl = GPIO_NUM_22;
#define I2C_NUM I2C_NUM_0
#define I2C_MASTER_FREQ_HZ 400000 /*!< I2C master clock frequency. no higher than 1MHz for now */

bmp280_t bmp280;
bmp280_params_t params;

void VEHICLE_BARO::init_barometer(void){
    i2c_config_t conf; // Note the opening brace here
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = i2c_gpio_sda;
    conf.scl_io_num = i2c_gpio_scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE,
    conf.master.clk_speed = I2C_MASTER_FREQ_HZ;
    conf.clk_flags = 0;

    //ESP_LOGI("TAG", "STR %s", "I2C Driver Init");
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM, &conf));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM, I2C_MODE_MASTER, 0, 0, 0));

    bmp280_init_desc(&bmp280, BMP280_I2C_ADDRESS_0, I2C_NUM,i2c_gpio_sda,i2c_gpio_scl);
    bmp280_init_default_params(&params);
    bmp280_init(&bmp280, &params);
}

float VEHICLE_BARO::pushTemperature(){
    init_barometer();
    float temperature, pressure;
    bmp280_read_float(&bmp280, &temperature, &pressure, nullptr);
    bmp280_free_desc(&bmp280);
    return temperature;
}

float VEHICLE_BARO::pushPressure(){
    init_barometer();
    float temperature, pressure;
    bmp280_read_float(&bmp280, &temperature, &pressure, nullptr);
    bmp280_free_desc(&bmp280);
    return pressure;
}