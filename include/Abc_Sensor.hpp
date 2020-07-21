//
// Created by hammer on 02/06/2020.
//

#ifndef REMOTESENSORS_SENSOR_HPP
#define REMOTESENSORS_SENSOR_HPP

#include <stdint-gcc.h>
#include <Thread.h>

class Sensor: public Thread
{
protected:
    Sensor(uint8_t sensorId, char sensorType, float reading, char type, char unit, uint8_t precision, uint8_t length):
            data(sensorId, sensorType, reading, type, unit, precision, length) {}
    virtual ~Sensor() = default;
    virtual void run() = 0;
    virtual void switch_units() = 0;

public:
    struct SensorData {
        uint8_t sensorId;
        char sensorType;
        float reading;
        char readingType;
        char unit;
        uint8_t precision;
        uint8_t length;
        SensorData() = default;
        SensorData(uint8_t sensorId, char sensorType, float reading, char type, char unit, uint8_t precision, uint8_t length):
                sensorId(sensorId), sensorType(sensorType), reading(reading), readingType(type), unit(unit), precision(precision), length(length) {}
    } data;

    float get_reading() const { return data.reading; }
    SensorData get_data() const { return data; }


};


#endif //REMOTESENSORS_SENSOR_HPP
