#include <Arduino.h>

#include "flashOneLed.cpp"
#include "flashTwoLedsSwitch.cpp"
#include "turnOutSolinoidButton.cpp"
#include "turnOutSolinoidSwitch.cpp"

  //flashOneLed led1(22, 200, 250);
  //flashOneLed led2(23, 200, 300);

  flashTwoLedsSwitch led3(23, 24, 26, 600);

  //turnOutSolinoidButton turnOut1 (22,26,23,24);

  //turnOutSolinoidSwitch turnOut2 (22,26,23,24);

void setup() {

}

void loop() {

  //led1.update();
  //led2.update();

  led3.update();

  //turnOut1.update();

  //turnOut2.update();

}