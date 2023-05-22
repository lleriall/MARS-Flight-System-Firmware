#include "module_router.h"

double MODULE_ROUTER::motors(uint8_t type, uint8_t value) {
  sendCommandWithValue("MOTORS:", type);
  sendCommandWithValue("", value);
  return receiveData();
}

void MODULE_ROUTER::readIMU(uint8_t variable) {
  sendCommandWithValue("IMU:", variable);
}

double MODULE_ROUTER::readGPS(uint8_t variable) {
  sendCommandWithValue("GPS:", variable);
  return receiveData();
}

uint8_t MODULE_ROUTER::initiateThrottle(uint8_t value) {
  sendCommandWithValue("THROTTLE:", value);
  return receiveData();
}

void MODULE_ROUTER::sendCommand(const char* command) {
  espSerial.println(command);
}

void MODULE_ROUTER::sendCommandWithValue(const char* command, uint8_t value) {
  espSerial.print(command);
  espSerial.println(value);
}

double MODULE_ROUTER::receiveData() {
  if (espSerial.available()) {
    return espSerial.parseFloat();
  }
  return 0.0;
}