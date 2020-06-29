//
// Created by hammer on 02/06/2020.
//

#ifndef REMOTESENSORS_SENSOR_HPP
#define REMOTESENSORS_SENSOR_HPP

#include <stdint-gcc.h>

class Sensor
{
protected:
    Sensor(float reading, char type, char unit, uint8_t precision, uint8_t length):
            reading(reading), type(type), unit(unit), precision(precision), length(length) {}
    virtual ~Sensor() = default;
    virtual void set_reading() = 0;
    virtual void switch_units() = 0;

    float reading;
    char type;
    char unit;
    uint8_t precision;
    uint8_t length;

public:
    float get_reading() const { return this->reading; }
    char get_type() const { return this->type; };
    char get_unit() const { return this->unit; };

};


#endif //REMOTESENSORS_SENSOR_HPP
