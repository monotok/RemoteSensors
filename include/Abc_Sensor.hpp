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
    Sensor(const char *sensorId, const char *sensorType, float reading, const char *unit):
            data(sensorId, sensorType, reading, unit) {}
    virtual ~Sensor() = default;
    virtual void run() = 0;
    virtual void switch_units() = 0;

public:
    struct SensorData {
        char sensorId[4] = {};
        char sensorType[4] = {};
        float reading;
        char unit[4] = {};
        SensorData() = default;
        SensorData(const char *sensorId, const char *sensorType, float reading, const char *unit): reading(reading) {
            strcpy(this->unit, unit);
            strcpy(this->sensorType, sensorType);
            strcpy(this->sensorId, sensorId);
        }
    } data;

    float get_reading() const { return data.reading; }
    SensorData get_data() const { return data; }


};


#endif //REMOTESENSORS_SENSOR_HPP
