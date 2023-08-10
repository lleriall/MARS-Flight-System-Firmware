#include"driver/uart.h"
#include "esp_log.h"
#include <cstring>
#include"atgm336H.h"

#define GPS_UART_NUM UART_NUM_1
#define GPIO_NUM_RX 3
#define GPIO_NUM_TX 1
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)
#define BUF_SIZE (1024)

void ATGM336H::init_ATGM_module(){
    //Configure parameters of an UART driver,
    //communication pins and install the driver 
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ESP_ERROR_CHECK(uart_driver_install(GPS_UART_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(GPS_UART_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(GPS_UART_NUM, GPIO_NUM_TX, GPIO_NUM_RX, ECHO_TEST_RTS, ECHO_TEST_CTS));
}

void ATGM336H::pullATGM_data(){
    //uint8_t data;
    //char nmea_buffer[128]; // Buffer to store NMEA sentence

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);

    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(GPS_UART_NUM, data, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        // Write data back to the UART
        uart_write_bytes(GPS_UART_NUM, (const char *) data, len);
        if (len) {
            data[len] = '\0';
            ESP_LOGI("TAG", "Recv str: %s", (char *) data);
        }
        vTaskDelay(1);
    }

    /*while (1) {
        // Read one byte from UART
        uart_read_bytes(GPS_UART_NUM, &data, 1, portMAX_DELAY);

        if (data == '\n') {
            // Print NMEA sentence buffer as a string
            ESP_LOGI("TAG", "Received NMEA: %s", nmea_buffer);
            memset(nmea_buffer, 0, sizeof(nmea_buffer)); // Clear buffer
        } else {
            // Append received byte to NMEA sentence buffer
            strncat(nmea_buffer, (const char *)&data, 1);
        }
    }*/
}
