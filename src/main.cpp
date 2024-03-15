#include <Arduino.h>

#include "flashOneLed.cpp"
#include "flashTwoLedsSwitch.cpp"
#include "flashTwoLedsSensors.cpp"
#include "turnOutSolinoidButton.cpp"
#include "turnOutSolinoidSwitch.cpp"

  //flashOneLed led1(22, 500, 1000);
  //flashOneLed led2(23, 200, 300);

  //flashTwoLedsSwitch flashSwitch(23, 24, 26, 600);

  flashTwoLedsSensors flashSensors(23, 24, 26, 0, 0, 0, 600, 2000);

  //turnOutSolinoidButton turnOutButton(22,26,23,24);

  //turnOutSolinoidSwitch turnOutSwitch(22,26,23,24);

void setup() {

}

void loop() {

  //led1.update();
  //led2.update();

  //flashSwitch.update();

  flashSensors.update();

  //turnOutButton.update();

  //turnOutSwitch.update();

}