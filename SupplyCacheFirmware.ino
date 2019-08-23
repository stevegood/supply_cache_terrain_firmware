
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

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  //initialize RFID module
  rfid.init();
}

boolean isOpen = false;

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
    if (!isOpen) {
      isOpen = rotate(135, isOpen); // move half speed clockwise
    }
  }
  else
  {
    log("Close");
    ledG.off();
    ledR.on();
    if (isOpen) {
      isOpen = rotate(45, isOpen); // move half speed counter-clockwise
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

boolean rotate(int speed, boolean state) {
  servo360Micro.attach(SERVO360MICRO_PIN_SIG);
  servo360Micro.write(speed); // move at input speed
  delay(1000);              // wait 1 second
  servo360Micro.write(90);  // stop the motor
  delay(500);               // wait half a second
  servo360Micro.detach();   // stop sending power to the motor
  return !state;
}