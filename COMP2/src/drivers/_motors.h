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

#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include<Arduino.h>
#include <Servo.h>

class ServoController {
    public:
        ServoController();
    public:
        void moveToAngleFL(int angle);
        void moveToAngleFR(int angle);
        void moveToAngleRL(int angle);
        void moveToAngleRR(int angle);

private:
    Servo servo_1;
    Servo servo_2; // servo controller (multiple can exist)
    Servo servo_3; // servo controller (multiple can exist)
    Servo servo_4; // servo controller (multiple can exist)

    int servo_pin1 = 3; // PWM pin for servo control
    int servo_pin2 = 2;
    int servo_pin3 = 6;
    int servo_pin4 = 5;
};

#endif  // SERVOCONTROLLER_H