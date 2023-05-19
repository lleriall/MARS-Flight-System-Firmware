/*#include "GPS.h"

GPS::GPS(HardwareSerial& serial) : serial_(serial) {}

void GPS::begin() {
  serial_.begin(9600, SERIAL_8N1, GPIO_NUM_1, GPIO_NUM_3);
}

void GPS::update() {
  while (serial_.available()) {
    String line = serial_.readStringUntil('\n');
    if (line.startsWith("$GPGGA")) {
      parseGGA(line);
    }
  }
}

float GPS::getLatitude() const {
  return latitude_;
}

float GPS::getLongitude() const {
  return longitude_;
}

float GPS::getAltitude() const {
  return altitude_;
}

void GPS::parseGGA(const String& line) {
  int index = 0;
  for (int i = 0; i < 6; ++i) {
    index = line.indexOf(',', index + 1);
  }
  if (line[index + 1] != ',') {
    latitude_ = parseCoord(line.substring(index + 1, index + 10), line[index + 11]);
    index = line.indexOf(',', index + 1);
    if (line[index + 1] == 'S') {
      latitude_ *= -1;
    }
    index = line.indexOf(',', index + 1);
    longitude_ = parseCoord(line.substring(index + 1, index + 10), line[index + 11]);
    index = line.indexOf(',', index + 1);
    if (line[index + 1] == 'W') {
      longitude_ *= -1;
    }
    index = line.indexOf(',', index + 1);
    altitude_ = line.substring(index + 1, line.indexOf(',', index + 1)).toFloat();
  }
}

float GPS::parseCoord(const String& coordStr, char hem) const {
  int degrees = coordStr.substring(0, 2).toInt();
  float minutes = coordStr.substring(2).toFloat();
  float coord = degrees + minutes / 60.0;
  if (hem == 'S' || hem == 'W') {
    coord *= -1;
  }
  return coord;
}*/