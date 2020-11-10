//
// Created by hammer on 11/06/2020.
//

#ifndef REMOTESENSORS_BATTERY_HPP
#define REMOTESENSORS_BATTERY_HPP

#include <Vcc.h>
#include "Abc_Sensor.hpp"

class Battery: public Sensor
{
public:
    Battery(const char *sensorId, const char *sensorType, float reading, const char *unit, float min, float max, float correction, int pin):
            Sensor(sensorId, sensorType, reading, unit), vcc(correction), VccMin(min), VccMax(max), lowBatteryPin(pin) {}
    void run() override;
    void switch_units() override;

    float checkBatteryRemaining();
    void setLowBatteryWarningLevel(float percent);

private:
    Vcc vcc;
    const float VccMin;           // Minimum expected Vcc level, in Volts.
    const float VccMax;           // Maximum expected Vcc level, in Volts.
    const int lowBatteryPin;
    float lowBatteryWarning = 30.0;

};


#endif //REMOTESENSORS_BATTERY_HPP
