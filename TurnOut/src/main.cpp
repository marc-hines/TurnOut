#include <Arduino.h>
#include "flasher.h"
#include "turnOutSolinoid.h"

  //flasher led1(22, 200, 200);
  //flasher led2(23, 200, 250);
  //flasher led3(24, 200, 300);
  //flasher led4(25, 200, 350);
  //flasher led5(26, 200, 400);

  turnOutSolinoid turnOut1 (22,26,24,25);

void setup() {

}

void loop() {

  //led1.update();
  //led2.update();
  //led3.update();
  //led4.update();
  //led5.update();

  turnOut1.update();

}