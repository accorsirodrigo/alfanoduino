#ifndef LapController_H
#define LapController_H

#include <Arduino.h>

class LapController
{
    private:
    public:
        LapController();
        void init();
        int getLaps();
        void startLap();
        void endLap();
        double lasLapTime();
        boolean isFirstLap();
        double getCurrentLapTime();
        double getBestLapTime();
        
};
#endif

extern LapController LapCont;