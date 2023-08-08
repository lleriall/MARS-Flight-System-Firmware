#include"bmp280.h"

class VEHICLE_BARO {
    public:
        static void init_barometer(void);

        static float pushTemperature();

        static float pushPressure();
};