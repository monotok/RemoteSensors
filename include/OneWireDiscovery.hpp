//
// Created by hammer on 29/10/2020.
//

#ifndef REMOTESENSORS_ONEWIREDISCOVERY_HPP
#define REMOTESENSORS_ONEWIREDISCOVERY_HPP

#include "OneWire.h"

class OneWireDiscovery
{
public:

    OneWireDiscovery(OneWire &oneWire, int errPinLed): oneWire(oneWire), pinLed(errPinLed) {};
    uint8_t* discoverNextOneWireDevice();

private:

    uint8_t foundSensor[8] = {};
    OneWire& oneWire;
    int pinLed;
};


#endif //REMOTESENSORS_ONEWIREDISCOVERY_HPP
