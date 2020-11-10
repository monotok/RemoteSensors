//
// Created by hammer on 29/10/2020.
//

#include "OneWireDiscovery.hpp"

uint8_t* OneWireDiscovery::discoverNextOneWireDevice()
{
    uint8_t i;
    uint8_t addr[8];     // enough room for 6 sensors
    uint8_t addrSub;

    if (oneWire.search(addr))
    {
        for(i = 0; i < 8; i++)
        {
            foundSensor[i] = addr[i];
        }
        if (OneWire::crc8(addr, 7) != addr[7])
        {
            digitalWrite(pinLed, HIGH);
        }
    }
    return foundSensor;
}
