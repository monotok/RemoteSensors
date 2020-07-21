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
 * lastly we have the reading unit eg: c or f
 *
 * Full example of sensor with 2x temp, 1 pressure sensor, 1 humidity sensor, 1 air quality
 *
 * 04tmf422033tmf421565pri401030hui2060aqi105
 */

#include <Arduino.h>
#include <DisplayController.hpp>
#include <Thread.h>
#include <ThreadController.h>
#include "BtnController.hpp"
#include "Sensor_T.hpp"
#include <Battery.hpp>
#include <Transit.hpp>

#define PUSH_BTN_PIN 10
#define ONE_WIRE_BUS 9

// Declare classes here so they are in scope of loop method
BtnController pushBtn1;
DisplayController dc;
ThreadController controller = ThreadController();
OneWire oneWire(ONE_WIRE_BUS);
Transit rf(5,11);

// Enable sensors based on build flags
Battery battery = Battery(0.0, 5.0, 1.0, 6);
Sensor_T temperature = Sensor_T(1,'t', 0, 'f', 'c', 2, 4, oneWire);
Sensor_T temperature2 = Sensor_T(1,'t', 33.76, 'f', 'c', 2, 4, oneWire);

// Add sensors to transmit via RF. Done this way so we can send each sensor individually in a short burst.
Thread rf_t1 = Thread();
Thread rf_t2 = Thread();

void setup()
{
    Serial.begin(9600);
    pinMode(PUSH_BTN_PIN, INPUT);
    dc.initialiseDisplay();
    dc.addSensorToDisplay(&temperature);
    dc.addSensorToDisplay(&temperature2);

    temperature.setInterval(10);
//    temperature2.setInterval(10000);
    rf_t1.setInterval(20000); // Setts the wanted interval to be 10ms
    rf_t1.onRun([](){ rf.transmitSensor(&temperature); });
    rf_t2.setInterval(30000); // Setts the wanted interval to be 10ms
    rf_t2.onRun([](){ rf.transmitSensor(&temperature2); });

    controller.add(&temperature);
//    controller.add(&temperature2);
    controller.add(&rf_t1);
    controller.add(&rf_t2);

//    randomSeed(analogRead(A0));  //initialize the random number generator with
//    //a random read from an unused and floating analog port
//    //to be able to transmit over rf at random times
//    unsigned long randNumber = random(10,20); //1 to 2 minutes to delay

}

void loop()
{
    pushBtn1.initBtnState(PUSH_BTN_PIN);
    if(pushBtn1.debounceBtn())
    {
        //display value on screen. For now write to serial line
        dc.displayNext();
        pushBtn1.updateLastDebounceTime();
    }
    pushBtn1.reInitBtnState();

    controller.run();

    dc.printCurrentSensor();
}