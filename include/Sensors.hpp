//
// Created by hammer on 02/06/2020.
//

#ifndef REMOTESENSORS_SENSORS_HPP
#define REMOTESENSORS_SENSORS_HPP

#define TEMP_POS 0

#include <stdint-gcc.h>
#include <DallasTemperature.h>

class Sensors
{
public:
    struct sensor {
        float reading;
        char type;
        uint8_t precision;
        uint8_t length;
        bool display;
    };

    void add_temp_sensor();
    sensor* get_temp_sensor();
    void check_temp(DallasTemperature dt, DeviceAddress probe);

private:
    void enable_sensor(sensor *sensor);
    sensor* enabledSensors[20] = { nullptr };
};


#endif //REMOTESENSORS_SENSORS_HPP
