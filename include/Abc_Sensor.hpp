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
    Sensor(const char *sensorId, float reading):
            data(sensorId, reading) {}
    virtual ~Sensor() = default;
    virtual void run() = 0;

public:
    struct SensorData {
        char sensorId[4] = {};
        float reading;
        SensorData() = default;
        SensorData(const char *sensorId, float reading): reading(reading) {
            strcpy(this->sensorId, sensorId);
        }
    } data;

    float get_reading() const { return data.reading; }
    SensorData get_data() const { return data; }


};


#endif //REMOTESENSORS_SENSOR_HPP
