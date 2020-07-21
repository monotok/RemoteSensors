//
// Created by hammer on 02/06/2020.
//

#include "Sensor_T.hpp"


Sensor_T::Sensor_T(uint8_t sensorId, char sensorType, float reading, char readingType, char unit, uint8_t precision, uint8_t length, OneWire &oneWire):
    Sensor(sensorId, sensorType, reading, readingType, unit, precision, length), dt(&oneWire) {}

void Sensor_T::run()
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    if (data.unit == 'c')
    {
        data.reading = dt.getTempC(probe);
    } else
    {
        data.reading = dt.getTempF(probe);
    }
    runned();
}

void Sensor_T::switch_units()
{
    if(data.unit == 'f')
        data.unit = 'c';
    else if(data.unit == 'c')
        data.unit = 'f';
}
