#ifndef ATGM336HX
#define ATGM336HX

class ATGM336H {
    public:
        static void init_ATGM_module();

        static void pullATGM_data();

        static double getLatitude();

        static double getLongitude();

        static double getAltitude();
};

#endif //ATGM336HX