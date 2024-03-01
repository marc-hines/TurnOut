#include <Arduino.h>

#include "turnOutSolinoidButton.cpp"
#include "turnOutSolinoidSwitch.cpp"
#include "flashOneLed.cpp"
#include "flashTwoLeds.cpp"

  //flashTwoLeds led1(22, 23, 26, 600);
  //flashOneLed led2(23, 200, 250);
  //flashOneLed led3(24, 200, 300);
  //flashOneLed led4(25, 2000, 2000);

  //turnOutSolinoidButton turnOut1 (22,26,23,24);

  turnOutSolinoidSwitch turnOut2 (26,23,24);

void setup() {

}

void loop() {

  //led1.update();
  //led2.update();
  //led3.update();
  //led4.update();

  //turnOut1.update();

  turnOut2.update();

}