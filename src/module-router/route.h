#ifndef MOD_ROUTER
#define MOD_ROUTER

#include"util/defi.h"

#define ESP_RX_PIN 2
#define ESP_TX_PIN 3

#define OPEN 1
#define CLOSE 0

#define READ 2

class MODULE_ROUTER {
public:
  MODULE_ROUTER() : espSerial(ESP_RX_PIN, ESP_TX_PIN) {}

  double motors(uint8_t type, uint8_t value);
  void readIMU(uint8_t variable);
  double readGPS(uint8_t variable);
  uint8_t initiateThrottle(uint8_t value);

private:
  SoftwareSerial espSerial;
  void sendCommand(const char* command);
  void sendCommandWithValue(const char* command, uint8_t value);
  double receiveData();
};

#endif // MOD_ROUTER