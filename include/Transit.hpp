//
// Created by hammer on 01/07/2020.
//

#ifndef REMOTESENSORS_TRANSIT_HPP
#define REMOTESENSORS_TRANSIT_HPP

#include <RH_ASK.h>
#include <SPI.h>
#include <Abc_Sensor.hpp>

class Transit
{
public:
    Transit(int ledPin, int radioTransmitterPin): ledPin(ledPin), Radio(2000, 0, radioTransmitterPin, 0) {
        pinMode(ledPin, OUTPUT);
    }

    void transmitSensor(Sensor *sensorToTransmit);
    void initialiseTransit();

private:
    const int ledPin;
    RH_ASK Radio;
};


#endif //REMOTESENSORS_TRANSIT_HPP
