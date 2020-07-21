//
// Created by hammer on 01/07/2020.
//

#ifndef REMOTESENSORS_TRANSIT_HPP
#define REMOTESENSORS_TRANSIT_HPP

#include <VirtualWire.h>
#include <RH_ASK.h>
#include <SPI.h>
#include <Abc_Sensor.hpp>

class Transit
{
public:
    Transit(int ledPin, int radioTransmitterPin): ledPin(ledPin), radioTransmitterPin(radioTransmitterPin), Radio(2000, 0, radioTransmitterPin, ledPin) {
        pinMode(ledPin, OUTPUT);
        pinMode(radioTransmitterPin, OUTPUT);
        Radio.init();
    }
    void transmitSensor(Sensor *sensorToTransmit);

private:
    const int ledPin;
    const int radioTransmitterPin;
    RH_ASK Radio;
};


#endif //REMOTESENSORS_TRANSIT_HPP
