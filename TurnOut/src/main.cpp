#include <Arduino.h>
#include "flasher1Pin.h"
#include "turnOutSolinoid.h"

  flasher1Pin led1(22, 200, 200);
  //flasher1Pin led2(23, 200, 250);
  //flasher1Pin led3(24, 200, 300);
  //flasher1Pin led4(25, 200, 350);
  //flasher1Pin led5(26, 200, 400);

  //turnOutSolinoid turnOut1 (22,26,24,25);

void setup() {

}

void loop() {

  led1.update();
  //led2.update();
  //led3.update();
  //led4.update();
  //led5.update();

  //turnOut1.update();

}