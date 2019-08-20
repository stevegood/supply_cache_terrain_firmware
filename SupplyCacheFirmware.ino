
// Include Libraries
#include "Arduino.h"
#include "LED.h"
#include "RFID.h"
#include "Servo.h"

// Pin Definitions
#define LEDG_PIN_VIN 3
#define LEDR_PIN_VIN 5
#define RFID_PIN_RST 2
#define RFID_PIN_SDA SS
#define SERVO360MICRO_PIN_SIG 4

// Global variables and defines

// object initialization
LED ledG(LEDG_PIN_VIN);
LED ledR(LEDR_PIN_VIN);
RFID rfid(RFID_PIN_SDA, RFID_PIN_RST);
Servo servo360Micro;

// define vars for testing menu
const int timeout = 10000; //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  //initialize RFID module
  rfid.init();
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{

  String rfidtag = rfid.readTag();
  log(rfidtag);

  if (rfidtag == "ca7235169b" || rfidtag == "8847426de")
  {
    log("Open");
    ledR.off();
    ledG.on();

    int pos = servo360Micro.read();
    if (pos < 180)
    {
      servo360Micro.attach(SERVO360MICRO_PIN_SIG);
      servo360Micro.write(180);
    }
    else
    {
      delay(1000);
      servo360Micro.detach();
    }
  }
  else
  {
    log("Close");
    ledG.off();
    ledR.on();

    int pos = servo360Micro.read();
    if (pos > 0)
    {
      servo360Micro.attach(SERVO360MICRO_PIN_SIG);
      servo360Micro.write(0);
    }
    else
    {
      delay(1000);
      servo360Micro.detach();
    }
  }
}

void log(String msg)
{
  if (Serial.availableForWrite())
  {
    Serial.println(msg);
  }
}