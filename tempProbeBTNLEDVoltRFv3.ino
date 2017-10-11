#include <DallasTemperature.h>
#include <OneWire.h>
#include <FourBitDisplay.h>
#include <stdio.h>
#include <Vcc.h>
#include <VirtualWire.h>
#include <Thread.h>
#include <ThreadController.h>

//Definitions
#define ONE_WIRE_BUS 9

//****Class declarations
FourBitDisplay fbd(8,4,3);
Thread myThread = Thread();
Thread battCheck = Thread();
Thread tempCheck = Thread();

//****Constant values
const int buttonPin = 10;
const float VccMin   = 0.0;           // Minimum expected Vcc level, in Volts.
const float VccMax   = 5.0;           // Maximum expected Vcc level, in Volts.
const float VccCorrection = 1.0/1.0;  // Measured Vcc by multimeter divided by reported Vcc
Vcc vcc(VccCorrection);
const int lowBattLED = 6; //Pin of connected RED LED
const int TransLED = 5; //Pin of connected RED LED
const int transmit_pin = 11; //RF Transmit PIN

//Other declarations, Button information
int buttonState;              // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int displayValToShow = 0;
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 200;    // the debounce time; increase if the output flickers

//Other declarations, Temperature readings
float temp, perBattLeft;

struct sensor_Data 
{
  int temperature; 
  char sensorID[10] = "BackBed";
  int perBatt;
};
sensor_Data sd;

//Serial number of each probe connected. Only Probe 2 is connected to this circuit.
DeviceAddress Probe01 = { 0x28, 0xFF, 0x97, 0xAA, 0xC2, 0x15, 0x01, 0x4D }; //Loft temp probe
DeviceAddress Probe02 = { 0x28, 0xFF, 0xB9, 0xEA, 0x21, 0x16, 0x04, 0xBE };
DeviceAddress Probe03 = { 0x28, 0xFF, 0xE5, 0x06, 0x02, 0x17, 0x04, 0xE5 }; //Dads temp probe

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

// void discoverOneWireDevices(OneWire availableSensors, byte ***foundSensors) 
// {
//   byte i;
//   byte addr[2][8];     // enough room for 2 sensors
//   byte addrSub;
//   *foundSensors = malloc(2*sizeof(byte)); //Create a 2d array in the heap for a single sensor

//   for(addrSub = 0; addrSub < 2; addrSub++)
//   {
//     if (availableSensors.search(addr[addrSub])) 
//     {
//       (*foundSensors)[addrSub] = malloc(8 * sizeof(byte));
//       for(i = 0; i < 8; i++)
//       {
//         foundSensors[addrSub][i] = addr[addrSub];
//       }
//       if (OneWire::crc8(addr[addrSub], 7) != addr[addrSub][7]) 
//       {
//         digitalWrite(lowBattLED, HIGH);
//         return;
//       } 
//     }
//   }
// }

void transmitTemp()
{
  sd.temperature = (int)(temp*100);
  sd.perBatt = (int)(perBattLeft*100);
  
  digitalWrite(TransLED, HIGH);
  vw_send((uint8_t *)&sd,sizeof(sd));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(TransLED, LOW);
}

void convertFloatToChar(float temp, char buf[4])
{
  if(temp < 100.0 && temp > -9.9)
  {
    dtostrf(temp,4, 2, buf); //Convert from float to char array
  }
  else
  {
    dtostrf(temp,4, 1, buf); //Convert from float to char array
  }
}

void checkBatt()
{
  //Check the battery percentage remaining for the LED
  perBattLeft = vcc.Read_Perc(VccMin, VccMax);
  if(perBattLeft <20)
    digitalWrite(lowBattLED, HIGH);
}

void checkTemp()
{
    sensors.setWaitForConversion(false);  // makes it async
    sensors.requestTemperatures();
    sensors.setWaitForConversion(true);
    temp = sensors.getTempC(Probe02);
}
 
void setup() 
{
  // start serial port
  Serial.begin(9600);

  randomSeed(analogRead(A0));  //initialize the random number generator with
                               //a random read from an unused and floating analog port
                               //to be able to transmit over rf at random times
  unsigned long randNumber = random(10,20); //1 to 2 minutes to delay                        
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  //Low battery PIN setup and Transmit LED
  pinMode(lowBattLED, OUTPUT);
  pinMode(TransLED, OUTPUT);

  //Transmit Stuff
  vw_set_tx_pin(transmit_pin);
  vw_setup(2000);       // Bits per sec

  //Discover connected onewire devices and store their serial number
  // byte **foundSensors;
  // discoverOneWireDevices(oneWire, &foundSensors);

  // for(int j = 0; j < 2; j++) 
  // {
  //   for(int i = 0; i < 8; i++) 
  //   {
  //      Serial.print(foundSensors[j][i], HEX);
  //   }
  //   Serial.print("\n");
  // }
  // char *stringTest1 = foundSensors[0];
  // Serial.print(*stringTest1, HEX);

  // Start up the library
  sensors.begin();
  sensors.setResolution(Probe02, 11);

  //This turns off the display so there is no initial rubbish on the display upon power on!
  fbd.printToDisplay("////",4,"r");

  //Thread stuff so I can transmit every so often
  myThread.enabled = true; // Default enabled value is true
  myThread.setInterval(randNumber*1000); // Setts the wanted interval to be 10ms
  myThread.onRun(transmitTemp);

  battCheck.enabled = true; // Default enabled value is true
  battCheck.setInterval(120000); // Setts the wanted interval to be 10ms
  battCheck.onRun(checkBatt);
  perBattLeft = vcc.Read_Perc(VccMin, VccMax); //Check now upon boot so it is not zero for two mins

  tempCheck.enabled = true; // Default enabled value is true
  tempCheck.setInterval(8); // Setts the wanted interval to be 10ms
  tempCheck.onRun(checkTemp);
}

void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  if(tempCheck.shouldRun())
  {
    tempCheck.run();
  }
  if(myThread.shouldRun())
  {
    // Yes, the Thread should be runned, let's run it
    myThread.run();
  }
  if(battCheck.shouldRun())
  {
    // Yes, the Thread should be runned, let's run it
    battCheck.run();
  }

  if (buttonState == HIGH && lastButtonState == LOW && millis() - lastDebounceTime > debounceDelay) 
  {
    displayValToShow++;
    if(displayValToShow > 3)
    {
      displayValToShow = 0; //Cycle round 3 times and fourth turn off display again
    }
    lastDebounceTime = millis();    
  }

  char buf[4]; //Later on for showing on display
  char *val;
  char *just = "r";
  float f;
  
  if(displayValToShow == 0)
  {
    val = "////";
  }
  else if(displayValToShow == 1)
  {
    convertFloatToChar(temp,buf);
    val = buf;
  }
  else if(displayValToShow == 2)
  {
    f = temp*1.8+32; //Convert to F
    convertFloatToChar(f,buf);
    val = buf;
  }
  else
  {
    convertFloatToChar(perBattLeft,buf);
    val = buf;
  }
  
  short arraySize = strlen(val);
  fbd.printToDisplay(val,arraySize,just);
  lastButtonState = buttonState;
}
  


