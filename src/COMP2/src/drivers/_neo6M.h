/*#ifndef NEO6M_H
#define NEO6M_H

//#include <SoftwareSerial.h>
//#include <TinyGPS++.h>

class NEO6M {
  public:
    void begin();

    bool readGPS();

    float getLatitude();

    float getLongitude();

    float getAltitude();
    
    int getSatellites();

  private:
    //SoftwareSerial gpsSerial{2, 3}; // RX, TX pins
    //TinyGPSPlus gps;
    float latitude = 0;
    float longitude = 0;
    float altitude = 0;
    int satellites = 0;
};

#endif
*/