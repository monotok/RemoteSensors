//
// Created by hammer on 11/06/2020.
//

#include "../include/Battery.hpp"

float Battery::checkBatteryRemaining()
{
    float batt = vcc.Read_Perc(VccMin, VccMax);
    if (batt < lowBatteryWarning)
        digitalWrite(lowBatteryPin, HIGH);
    else
        digitalWrite(lowBatteryPin, LOW);
    return batt;
}

void Battery::setLowBatteryWarningLevel(float percent)
{
    lowBatteryWarning = percent;
}

void Battery::run()
{
    data.reading = checkBatteryRemaining();
    runned();
}

void Battery::switch_units()
{
}
