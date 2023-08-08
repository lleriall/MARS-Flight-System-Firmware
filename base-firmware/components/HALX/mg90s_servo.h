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

#ifndef MG90S_SERVO_H
#define MG90S_SERVO_H

#include <cstdint>

#define SPEED_DEFAULT 1
#define SPEED_FAST 20

class WingTranslate {
    public:
        static void mcpwm_gpio_initialize(uint8_t motor);

        static uint32_t servo_per_degree_init(uint32_t degree_of_rotation);
        
        uint8_t mcpwm_servo_control(uint32_t angle,uint8_t pin, uint8_t speed);

    private:
        uint8_t GET_SERVO_POS(uint8_t pin);

        void UPDATE_SERVO_POS(uint8_t pin, uint8_t updatedValue);
};

#endif // MG90S_SERVO_H