#include "GPS.h"

GPS::GPS(double lat, double log)
{
  this->lat = lat;
  this->log = log;
  init();
}

GPS::GPS()
{
  init();
}

void GPS::init()
{
}

void GPS::set(double lat, double log)
{
  this->lat = lat;
  this->log = log;
}

double GPS::getLat()
{
  return this->lat;
}

double GPS::getLng()
{
  return this->log;
}