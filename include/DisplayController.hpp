//
// Created by hammer on 07/06/2020.
//

#ifndef REMOTESENSORS_DISPLAYCONTROLLER_HPP
#define REMOTESENSORS_DISPLAYCONTROLLER_HPP
#define byte unsigned char

#include "FourBitDisplay.h"
#include "Abc_Sensor.hpp"

class DisplayController
{
public:
    DisplayController();
    void initialiseDisplay();
    void printFloat(float val);
    void printCurrentSensor();
    void displayNext();
    void addSensorToDisplay(Sensor *sensorToDisplay);
    Sensor* getCurrentSensor();
//    void addBatteryDisplay(Battery *b);

private:
    FourBitDisplay fbd;
    char buf[6] = {};

    int currentSensorIndex = 0;
    Sensor *currentSensor = { nullptr };
    Sensor *sensorsDisplayed[10] = { nullptr };

//    Battery *battery = nullptr;

};


#endif //REMOTESENSORS_DISPLAYCONTROLLER_HPP
