/*#include <Wire.h>
#include<Arduino.h>
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

void setup() {
   Serial.begin(115200);
   Wire.begin(21, 22, 100000); // sda, scl, clock speed
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x6B);  // PWR_MGMT_1 register
   Wire.write(0);     // set to zero (wakes up the MPU−6050)
   Wire.endTransmission(true);
   Serial.println("Setup complete");
}

void loop() {
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(false);
   Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers
   AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
   AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) &  0x42 (TEMP_OUT_L)
   GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
   GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
   GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

   float accel_x = AcX / 16384.0;
   float accel_y = AcY / 16384.0;
   float accel_z = AcZ / 16384.0;
   float temperature = (Tmp / 340.0) + 36.53;
   float gyro_x = GyX / 131.0;
   float gyro_y = GyY / 131.0;
   float gyro_z = GyZ / 131.0;

   Serial.print("Accel: ");
   Serial.print(accel_x);
   Serial.print(", ");
   Serial.print(accel_y);
   Serial.print(", ");
   Serial.print(accel_z);
   Serial.print(", Temp: ");
   Serial.print(temperature);
   Serial.print(", Gyro: ");
   Serial.print(gyro_x);
   Serial.print(", ");
   Serial.print(gyro_y);
   Serial.print(", ");
   Serial.print(gyro_z);
   Serial.println();
}
*/
#include<Arduino.h>
#include"_motors.h"

int count = 0;

void setup(){
   Serial.begin(9600);
}

void loop(){
   ServoController *obj = new ServoController();
   for(int count = 0; count < 180; count++){
      obj -> moveToAngleFL(count);
      obj -> moveToAngleFR(count);
      obj -> moveToAngleRL(count);
      obj -> moveToAngleRR(count);
   }
   
   delete obj;
}