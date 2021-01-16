//
// Created by hammer on 02/06/2020.
//

#include "Sensor_T.hpp"


Sensor_T::Sensor_T(const char *sensorId, float reading, OneWire &oneWire, OneWireDiscovery& owd):
    Sensor(sensorId, reading), dt(&oneWire), owd(owd) {
    getOneWireAddress();
}

void Sensor_T::run()
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    data.reading = dt.getTempC(probe);
    runned();
}


void Sensor_T::getOneWireAddress()
{
    uint8_t* tmp = owd.discoverNextOneWireDevice();
    for (int i = 0; i < 8; ++i) {
        probe[i] = *(tmp+i);
    }
}

