#include "LapController.h"

LapController LapCont;

long currentMillis = 0;
long lapTime = 0;
long bestLapTime = 0;
int laps = 0;

void resetDisplay()
{
    laps = 0;
    currentMillis = 0;
    bestLapTime = 0;
}

LapController::LapController()
{
    init();
}

void LapController::init() {}
int LapController::getLaps()
{
    return laps;
}

void LapController::startLap()
{
    currentMillis = millis();
    laps++;
}

void LapController::endLap()
{
    lapTime = millis() - currentMillis;
    if (lapTime < bestLapTime || bestLapTime == 0)
    {
        bestLapTime = lapTime;
    }

    startLap();
}

double LapController::lasLapTime()
{
    return lapTime / 1000.0;
}

boolean LapController::isFirstLap()
{
    return laps == 0;
}

double LapController::getCurrentLapTime()
{
    if(laps == 0)
    {
        return 0.0;
    }

    double currentTurnTime = (millis() - currentMillis) / 1000.0;
    if (currentTurnTime > 240000)
        resetDisplay();

    return currentTurnTime;
}

double LapController::getBestLapTime()
{
    return bestLapTime / 1000.0;
}
//
