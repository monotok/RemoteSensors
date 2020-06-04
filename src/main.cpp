/*
 * REQUIREMENTS:
 * Different .ino file for each type of sensor. Eg:
 * RS_Mains_Temp_Hum_Press.ino
 *
 * In sensor data structure define a type which can be decoded by other end to figure out what sensors the remote supports
 * Eg: char[20] type = "thp"
 * Rules for sending array
 * char sensorData[20]
 * always start with sensor id in format (int) <xx> eg: 04
 * then we have first sensor eg: temperature.
 * first 2 letters is type. eg: tm (temp)
 * then we have type, float or int eg: f or i
 * then we have width of reading. eg: 4
 * then we have precision of reading (values after the dot if a float, if int then set to 0) eg: 2
 * next is the reading, in this case it is 4 long. 2345
 *
 * Full example of sensor with 2x temp, 1 pressure sensor, 1 humidity sensor, 1 air quality
 *
 * 04tmf422033tmf421565pri401030hui2060aqi105
 */

#include <Arduino.h>
#include "BtnController.hpp"
#include "Sensors.hpp"

#define PUSH_BTN_PIN 10
#define ONE_WIRE_BUS 9

// Declare classes here so they are in scope of loop method
BtnController pushBtn1;
// Enable sensors based on build flags
Sensors sensors;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature dt(&oneWire);
DeviceAddress probe = { 0x28, 0xFF, 0xE5, 0x06, 0x02, 0x17, 0x04, 0xE5 }; //Miniature temp probe

void setup()
{
    Serial.begin(9600);
    pinMode(PUSH_BTN_PIN, INPUT);

    sensors.add_temp_sensor();
}

void loop()
{
    pushBtn1.initBtnState(PUSH_BTN_PIN);
    if(pushBtn1.debounceBtn())
    {
        //display value on screen. For now write to serial line
        Serial.print("Reading: ");
        sensors.check_temp(dt, probe);
        Serial.print(sensors.get_temp_sensor()->reading);
        Serial.print("\n");
        pushBtn1.updateLastDebounceTime();
    }
    pushBtn1.reInitBtnState();
}