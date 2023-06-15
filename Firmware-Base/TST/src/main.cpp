#include <Arduino.h>
#include"sender.h"

Sender *obj2 = new Sender(23,22);

void setup() {
  obj2 -> setup();
}

void loop() {
  Serial.println(obj2 -> receiveData());
  String dataToSend = "PACKET";  // Replace with your desired string
  obj2 -> sendData(dataToSend);
  delay(1000);
}