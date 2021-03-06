//
// Created by hammer on 02/06/2020.
//

#ifndef REMOTESENSORS_SENSOR_T_HPP
#define REMOTESENSORS_SENSOR_T_HPP

#include <Abc_Sensor.hpp>
#include <DallasTemperature.h>
#include "OneWireDiscovery.hpp"

class Sensor_T : public Sensor
{
public:
    Sensor_T(const char *sensorId, float reading, OneWire &oneWire, OneWireDiscovery& owd);
    void run() override;


private:
    DallasTemperature dt;
    OneWireDiscovery owd;
    DeviceAddress probe = {};
    void getOneWireAddress();

};


#endif //REMOTESENSORS_SENSOR_T_HPP
