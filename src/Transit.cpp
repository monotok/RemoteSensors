//
// Created by hammer on 01/07/2020.
//

#include "../include/Transit.hpp"

void Transit::transmitSensor(Sensor *sensorToTransmit)
{
    Radio.waitPacketSent();
    Radio.send((uint8_t *)&sensorToTransmit->data, sizeof(Sensor::SensorData));
}

