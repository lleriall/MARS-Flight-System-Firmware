#ifndef MG90S_SERVO_H
#define MG90S_SERVO_H

#include <cstdint>

class WingTranslate {
    public:
        static void mcpwm_gpio_initialize(uint8_t motor);

        static uint32_t servo_per_degree_init(uint32_t degree_of_rotation);
        
        uint8_t mcpwm_servo_control(uint32_t angle,uint8_t pin);

    private:
        uint8_t GET_SERVO_POS(uint8_t pin);

        void UPDATE_SERVO_POS(uint8_t pin, uint8_t updatedValue);
};

#endif // MG90S_SERVO_H