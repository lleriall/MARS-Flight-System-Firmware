#include "mpu6050.h"
#include <Wire.h>

MPU6050::MPU6050() {
    accelX = 0.0;
    accelY = 0.0;
    accelZ = 0.0;
    gyroX = 0.0;
    gyroY = 0.0;
    gyroZ = 0.0;
    pitch = 0.0;
    roll = 0.0;
    yaw = 0.0;
}

void MPU6050::initialize() {
    // Initialize MPU6050 sensor
    Wire.begin();
    Wire.beginTransmission(0x68); // Address of MPU6050
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0); // Wake up MPU6050
    Wire.endTransmission(true);
}

void MPU6050::update() {
    // Read sensor data from MPU6050
    Wire.beginTransmission(0x68); // Address of MPU6050
    Wire.write(0x3B); // Starting register for accelerometer data
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 14, true); // Request 14 bytes of data

    // Read accelerometer data
    accelX = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accelY = (Wire.read() << 8 | Wire.read()) / 16384.0;
    accelZ = (Wire.read() << 8 | Wire.read()) / 16384.0;

    // Read gyroscope data
    gyroX = (Wire.read() << 8 | Wire.read()) / 131.0;
    gyroY = (Wire.read() << 8 | Wire.read()) / 131.0;
    gyroZ = (Wire.read() << 8 | Wire.read()) / 131.0;

    // Calculate pitch, roll, and yaw angles
    pitch = fastAtan(-accelX / fastSqrt(accelY * accelY + accelZ * accelZ));
    roll = fastAtan(accelY / fastSqrt(accelX * accelX + accelZ * accelZ));
    yaw = fastAtan(accelZ / fastSqrt(accelX * accelX + accelY * accelY));
}

float MPU6050::getPitch() {
    return pitch;
}

float MPU6050::getRoll() {
    return roll;
}

float MPU6050::getYaw() {
    return yaw;
}

float MPU6050::fastAtan(float x) {
    // Approximation of arctan function
    const float a = 0.596227f;
    const float b = 1.570796f;
    const float c = 0.146446f;

    float y = a * x * x * x + b * x + c * x * x * x * x;

    return y;
}

float MPU6050::fastSqrt(float x) {
    // Approximation of square root function
    float y = x;
    float z = 0.0;
    while (y - z >= 0.0001) {
        y = (y + z) / 2.0;
        z = x / y;
    }

    return y;
}