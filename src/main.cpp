#include <Arduino.h>
#include "classes.cpp"

  //flasher3Pin led1(22, 23, 26, 600);
  //flasher1Pin led2(23, 200, 250);
  //flasher1Pin led3(24, 200, 300);
  //flasher1Pin led4(25, 1000, 1000);

  turnOutSolinoid turnOut1 (22,26,23,24);

void setup() {

}

void loop() {

  //led1.update();
  //led2.update();
  //led3.update();
  //led4.update();

  turnOut1.update();

}