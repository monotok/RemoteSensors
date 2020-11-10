//
// Created by hammer on 01/07/2020.
//

#ifndef REMOTESENSORS_TRANSIT_HPP
#define REMOTESENSORS_TRANSIT_HPP

#include <RH_RF69.h>
#include <SPI.h>
#include <Abc_Sensor.hpp>

class Transit
{
public:
    Transit(int ledPin, short ledErrPin, short csPin, short intPin, short rstPin, float frequency);
    void transmitSensor(Sensor *sensorToTransmit);
    void initialiseTransit();

private:
    const int ledPin;
    const int ledErrPin;
    const short rstPin;
    const float frequency;
    RH_RF69 Radio;

    void setRadioFrequency();
    void setRadioPower();

    [[noreturn]] void flashErrLed();
};


#endif //REMOTESENSORS_TRANSIT_HPP
