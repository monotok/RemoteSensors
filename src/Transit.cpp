//
// Created by hammer on 01/07/2020.
//

#include "../include/Transit.hpp"

void Transit::transmitSensor(Sensor *sensorToTransmit)
{
    digitalWrite(ledPin, HIGH);
    Radio.send((uint8_t *)&sensorToTransmit->data, sizeof(Sensor::data));
    Radio.waitPacketSent();
    digitalWrite(ledPin, LOW);
}

void Transit::initialiseTransit()
{
    Radio.init();
}

