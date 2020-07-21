//
// Created by hammer on 02/06/2020.
//

#ifndef REMOTESENSORS_SENSOR_T_HPP
#define REMOTESENSORS_SENSOR_T_HPP

#include <Abc_Sensor.hpp>
#include <DallasTemperature.h>

class Sensor_T : public Sensor
{
public:
    Sensor_T(uint8_t sensorId, char sensorType, float reading, char readingType, char unit, uint8_t precision, uint8_t length, OneWire &oneWire);
    void run() override;
    void switch_units() override;


private:
    DallasTemperature dt;
    DeviceAddress probe = { 0x28, 0xFF, 0xE5, 0x06, 0x02, 0x17, 0x04, 0xE5 }; //Miniature temp probe

};


#endif //REMOTESENSORS_SENSOR_T_HPP
