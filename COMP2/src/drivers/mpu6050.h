#ifndef MPU6050_H
#define MPU6050_H

class MPU6050 {
public:
    MPU6050();
    void initialize();
    void update();
    float getPitch();
    float getRoll();
    float getYaw();

private:
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    float pitch, roll, yaw;

    float fastAtan(float x);
    float fastSqrt(float x);
};

#endif

/*
    Sample:
    #include <Wire.h>
#include "mpu.h"

MPU6050 mpu;

void setup() {
  Serial.begin(9600);

  // Initialize MPU6050
  mpu.initialize();
}

void loop() {
  // Update sensor data
  mpu.update();

  // Get pitch, roll, and yaw angles
  float pitch = mpu.getPitch();
  float roll = mpu.getRoll();
  float yaw = mpu.getYaw();

  // Print the angles
  Serial.print("Pitch: ");
  Serial.print(pitch);
  Serial.print(" degrees\t");

  Serial.print("Roll: ");
  Serial.print(roll);
  Serial.print(" degrees\t");

  Serial.print("Yaw: ");
  Serial.print(yaw);
  Serial.println(" degrees");

  delay(500);  // Delay for readability
}





*/