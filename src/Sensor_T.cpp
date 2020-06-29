//
// Created by hammer on 02/06/2020.
//

#include "Sensor_T.hpp"


Sensor_T::Sensor_T(float reading, char type, char unit, uint8_t precision, uint8_t length, OneWire &oneWire):
    Sensor(reading, type, unit, precision, length), dt(&oneWire) {}

void Sensor_T::set_reading()
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    if (unit == 'c')
    {
        reading = dt.getTempC(probe);
    } else
    {
        reading = dt.getTempF(probe);
    }
}

void Sensor_T::switch_units()
{
    if(unit == 'f')
        unit = 'c';
    else if(unit == 'c')
        unit = 'f';
}
