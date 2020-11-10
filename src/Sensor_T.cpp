//
// Created by hammer on 02/06/2020.
//

#include "Sensor_T.hpp"


Sensor_T::Sensor_T(const char *sensorId, const char *sensorType, float reading, const char *unit, OneWire &oneWire, OneWireDiscovery& owd):
    Sensor(sensorId, sensorType, reading, unit), dt(&oneWire), owd(owd) {
    getOneWireAddress();
}

void Sensor_T::run()
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    if (strcmp(data.unit, "cel") == 0)
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
    if(strcmp(data.unit, "far") == 0)
        strcpy(data.unit, "cel");
    else if(strcmp(data.unit, "cel") == 0)
        strcpy(data.unit, "far");
}

void Sensor_T::getOneWireAddress()
{
    uint8_t* tmp = owd.discoverNextOneWireDevice();
    for (int i = 0; i < 8; ++i) {
        probe[i] = *(tmp+i);
    }
}

