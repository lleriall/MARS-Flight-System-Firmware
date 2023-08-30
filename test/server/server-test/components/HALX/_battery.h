#ifndef _BATTERY_
#define _BATTERY_

class BATTERY{
    public:
        void batteryInterfaceInit();
        
        double returnBatteryVoltage();

        double returnBatteryCurrentDraw();

        double returnBatteryPercent();
};

#endif //BATTERY