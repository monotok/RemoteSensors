//
// Created by hammer on 07/06/2020.
//

#include <stdlib.h>
#include <string.h>
#include <Battery.hpp>
#include "DisplayController.hpp"

DisplayController::DisplayController() : fbd(8,4,3) { }

void DisplayController::initialiseDisplay()
{
    fbd.printToDisplay("////",4,"l");
}

void DisplayController::printFloat(float val)
{
    dtostrf(val, 4, 2, buf);
    fbd.printToDisplay(buf, strlen(buf), "l");
}

void DisplayController::printCurrentSensor()
{
    printFloat(currentSensor->get_reading());
}

void DisplayController::displayNext()
{
    currentSensorIndex ++;
    if (currentSensorIndex > 7)
        currentSensorIndex = 0;
    if (sensorsDisplayed[currentSensorIndex] == nullptr)
        currentSensorIndex = 0;
    currentSensor = sensorsDisplayed[currentSensorIndex];
}

void DisplayController::addSensorToDisplay(Sensor *sensorToDisplay)
{
    for (auto &s : sensorsDisplayed)
    {
        if(s == nullptr)
        {
            s = sensorToDisplay;
            break;
        }
    }
    currentSensor = sensorsDisplayed[0];
}

Sensor* DisplayController::getCurrentSensor()
{
    return currentSensor;
}



