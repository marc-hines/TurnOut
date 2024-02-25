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

    digitalWrite(mcForwardPin, LOW);
    digitalWrite(mcReversePin, LOW);

    turnOutState = LOW;
    previousButtonState = HIGH;
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
    if (currentMillis - previousButtonPressMillis >= 500)
    {
        // If button is low, it is being pressed
        int currentButtonState = digitalRead(buttonPin);
        if (currentButtonState == HIGH)
        {
            previousButtonState = HIGH;
        }
        if (currentButtonState == LOW && previousButtonState == HIGH)
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
            previousButtonPressMillis = currentMillis;
            previousSoliniodMillis = currentMillis;
            previousButtonState = LOW;
        }
    }
}
