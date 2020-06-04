//
// Created by hammer on 02/06/2020.
//

#include "Sensors.hpp"


void Sensors::enable_sensor(sensor* sensor)
{
    for (auto & enabledSensor : enabledSensors)
    {
        if(enabledSensor == nullptr)
        {
            enabledSensor = sensor;
        }
    }
}

void Sensors::check_temp(DallasTemperature dt, DeviceAddress probe)
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    get_temp_sensor()->reading = dt.getTempC(probe);
}

void Sensors::add_temp_sensor()
{
    sensor temp{.reading=0, .type='t', .precision=2, .length=4, .display=true};
    enabledSensors[TEMP_POS] = &temp;
}

Sensors::sensor* Sensors::get_temp_sensor()
{
    return enabledSensors[TEMP_POS];
}