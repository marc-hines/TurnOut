#ifndef TURNOUT_SOLINOID_H
#define TURNOUT_SOLINOID_H

#include <Arduino.h>

class turnOutSolinoid
{
    int ledPin;
    int buttonPin;
    int mcForwardPin;
    int mcReversePin;

    int turnOutState;
    unsigned long previousButtonPressMillis;
    unsigned long previousSoliniodMillis;

  public:

    turnOutSolinoid (int _ledPin, int _buttonPin, int _mcForwardPin, int _mcReversePin);
    void update();

};

#endif