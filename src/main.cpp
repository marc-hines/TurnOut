#include <Arduino.h>

#include "flashOneLed.cpp"
#include "flashTwoLedsSwitch.cpp"
#include "flashTwoLedsSensors.cpp"
#include "turnOutSolinoidButton.cpp"
#include "turnOutSolinoidSwitch.cpp"
#include "doubleSignal.cpp"

/*
flashOneLed flashLed;

void setup() {
    flashLed.setLedPin(22);
    flashLed.setOnDuration(500);    // Optional
    flashLed.setOffDuration(1000);  // Optional
}

void loop() {
    flashLed.loop();
}
*/

/*
flashTwoLedsSwitch flashSwitch;

void setup() {
    flashSwitch.setLedPins(23, 24);
    flashSwitch.setSwitchPin(26);
    flashSwitch.setFlashDuration(500); // Optional
}

void loop() {
    flashSwitch.loop();
}
*/
/*
flashTwoLedsSensors flashSensors;

void setup() {
    flashSensors.setLedPins(23, 24);
    flashSensors.setSensor1Pin(26);
    flashSensors.setSensor2Pin(0);       // Optional
    flashSensors.setSensor3Pin(0);       // Optional
    flashSensors.setSensor4Pin(0);       // Optional
    flashSensors.setFlashDuration(500);  // Optional 
    flashSensors.setTurnOffDelay(2000);  // Optional
}

void loop() {
  flashSensors.loop();
}
*/

/*
turnOutSolinoidButton turnOutButton;

void setup() {
    turnOutButton.setLedPin(22);
    turnOutButton.setButtonPin(26);
    turnOutButton.setSolinoidPins(23,24);
}

void loop() {
    turnOutButton.loop();
}
*/

turnOutSolinoidSwitch turnOutSwitch;

void setup() {
    turnOutSwitch.setLedPin(22);
    turnOutSwitch.setSwitchPin(26);
    turnOutSwitch.setSolinoidPins(23,24);
}

void loop() {
    turnOutSwitch.loop();
}
