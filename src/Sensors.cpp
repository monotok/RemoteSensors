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

void Sensors::check_temp(DallasTemperature& dt, DeviceAddress probe)
{
    dt.setWaitForConversion(false);  // makes it async
    dt.requestTemperatures();
    dt.setWaitForConversion(true);
    if (get_temp_sensor()->unit == 'c')
    {
        get_temp_sensor()->reading = dt.getTempC(probe);
    } else
    {
        get_temp_sensor()->reading = dt.getTempF(probe);
    }

}

void Sensors::add_temp_sensor()
{
    auto* temp = new sensor{.reading=0, .type='t', .unit='c', .precision=2, .length=4, .display=true};
    enabledSensors[TEMP_POS] = temp;
}

Sensors::sensor* Sensors::get_temp_sensor()
{
    return enabledSensors[TEMP_POS];
}