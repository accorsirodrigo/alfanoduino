#include "Track.h"

Track::Track(double lat, double lng)
{
    this->lat = lat;
    this->lng = lng;
    init();
}

Track::Track(double lat, double lng, double tolerance)
{
    this->lat = lat;
    this->lng = lng;
    this->tolerance = tolerance;
    init();
}

void Track::init()
{
}

double Track::getLat()
{
    return lat;
}

double Track::getLng()
{
    return lng;
}

double Track::toleranceInSeconds()
{
    return tolerance;
}

boolean Track::checkPositionLine(double curLat, double curLng)
{
    
}

double Track::getTolerance()
{
    return tolerance;
}