#include <Arduino.h>
#include "turnOutSolinoid.h"

turnOutSolinoid::turnOutSolinoid (int _ledPin, int _buttonPin, int _mcForwardPin, int _mcReversePin)
{
    ledPin = _ledPin;
    buttonPin = _buttonPin;
    mcForwardPin = _mcForwardPin;
    mcReversePin = _mcReversePin;

    pinMode(ledPin, OUTPUT); 
    pinMode(buttonPin, INPUT_PULLUP); 
    pinMode(mcForwardPin, OUTPUT); 
    pinMode(mcReversePin, OUTPUT); 

    turnOutState = LOW;
    previousButtonPressMillis = 0;
    previousSoliniodMillis = 0;
}

void turnOutSolinoid::update()
{
    unsigned long currentMillis = millis();

    // We don't want the solinoid powered
    // for more than about 1/4 second.
    if (currentMillis - previousSoliniodMillis >= 250)
    {
        digitalWrite(mcForwardPin, LOW);
        digitalWrite(mcReversePin, LOW);
    }

    // Ignore any new button press for a bit - debounce
    if (currentMillis - previousButtonPressMillis >= 300)
    {
        // If button is low, it has been pressed
        int buttonState = digitalRead(buttonPin);
        if (buttonState == LOW )
        {
            if (turnOutState == LOW)
            {
                turnOutState = HIGH;
                digitalWrite(mcForwardPin, HIGH);
                digitalWrite(mcReversePin, LOW);
            }
            else
            {
                turnOutState = LOW;
                digitalWrite(mcForwardPin, LOW);
                digitalWrite(mcReversePin, HIGH);
            }
            digitalWrite(ledPin, turnOutState);
            previousSoliniodMillis = currentMillis;
        }
    }
}
