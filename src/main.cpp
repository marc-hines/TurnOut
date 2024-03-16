#include <Arduino.h>

#include "flashOneLed.cpp"
#include "flashTwoLedsSwitch.cpp"
#include "flashTwoLedsSensors.cpp"
#include "turnOutSolinoidButton.cpp"
#include "turnOutSolinoidSwitch.cpp"
#include "doubleSignal.cpp"

  flashOneLed flashLed;

  //flashTwoLedsSwitch flashSwitch(23, 24, 26, 600);

  //flashTwoLedsSensors flashSensors(23, 24, 26, 0, 0, 0, 600, 2000);

  //turnOutSolinoidButton turnOutButton(22,26,23,24);

  //turnOutSolinoidSwitch turnOutSwitch(22,26,23,24);

void setup() {

  flashLed.setLedPin(22);
  flashLed.setTimers(500, 1000);

}

void loop() {

  flashLed.loop();

  //flashSwitch.loop();

  //flashSensors.loop();

  //turnOutButton.loop();

  //turnOutSwitch.loop();

}