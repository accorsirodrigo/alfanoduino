#ifndef Track_H
#define Track_H

#include <Arduino.h>

class Track 
{
    private:
        double lat;
        double lng;
        double tolerance; //in meters
        double toleranceInSeconds();
    public:
        Track(double lat, double lng);
        Track(double lat, double lng, double tolerance);
        void init();
        double getLng();
        double getLat();
        boolean checkPositionLine(double curLat, double curLng);
        double getTolerance();
};

#endif