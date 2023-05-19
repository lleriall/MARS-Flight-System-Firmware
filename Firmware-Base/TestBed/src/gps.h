/*#ifndef GPS_H
#define GPS_H

#include <HardwareSerial.h>

class GPS {
public:
  GPS(HardwareSerial& serial);
  void begin();
  void update();
  float getLatitude() const;
  float getLongitude() const;
  float getAltitude() const;

private:
  HardwareSerial& serial_;
  float latitude_ = 0.0;
  float longitude_ = 0.0;
  float altitude_ = 0.0;

  void parseGGA(const String& line);
  float parseCoord(const String& coordStr, char hem) const;
};

#endif  // GPS_H*/