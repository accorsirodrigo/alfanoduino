#ifndef MY_GPS_H
#define MY_GPS_H

#include <Arduino.h>

class GPS {
    private:
        double lat;
        double log;
    public:
        GPS();
        GPS(double lat, double log);
        void init();
        void set(double lat, double lng);
        double getLat();
        double getLng();
};

#endif