#include <Arduino.h>

class turnOutSolinoidSwitch
{
    int ledPin;
    int switchPin;
    int mcForwardPin;
    int mcReversePin;

    int previousTurnOutState;
    int previousSwitchState;
    unsigned long previousSwitchDownMillis;
    unsigned long previousSwitchUpMillis;
    unsigned long previousSoliniodMillis;

  public:

    turnOutSolinoidSwitch (int _ledPin, int _switchPin, int _mcForwardPin, int _mcReversePin)
    {
        ledPin = _ledPin;
        switchPin = _switchPin;
        mcForwardPin = _mcForwardPin;
        mcReversePin = _mcReversePin;

        pinMode(ledPin, OUTPUT); 
        pinMode(switchPin, INPUT_PULLUP); 
        pinMode(mcForwardPin, OUTPUT); 
        pinMode(mcReversePin, OUTPUT); 

        digitalWrite(mcForwardPin, LOW);
        digitalWrite(mcReversePin, LOW);

        previousSwitchState = !(digitalRead(switchPin));
        previousTurnOutState = !(previousSwitchState);
        previousSwitchDownMillis = 0;
        previousSwitchUpMillis = 0;
        previousSoliniodMillis = 0;
    }

    void update()
    {
        int turnOutState;
        unsigned long currentMillis = millis();

        // We don't want the solinoid powered for more
        // than about 20 milliseconds to avoid damaging it
        if (currentMillis - previousSoliniodMillis >= 20)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, LOW);
        }

        int currentSwitchState = digitalRead(switchPin);

        // Ignore any additional changes after a switch change - "debounce"
        if (currentMillis - previousSwitchDownMillis >= 200 && currentMillis - previousSwitchUpMillis >= 200 )
        {
            if (currentSwitchState == HIGH && previousSwitchState == LOW)
            {
                previousSwitchState = HIGH;
                previousSwitchUpMillis = currentMillis;
                previousSoliniodMillis = currentMillis;
                activateSolinoid(LOW);
            }
            if (currentSwitchState == LOW && previousSwitchState == HIGH)
            {
                previousSwitchState = LOW;
                previousSwitchDownMillis = currentMillis;
                previousSoliniodMillis = currentMillis;
                activateSolinoid(HIGH);
            }
        }
    }

    void activateSolinoid(int turnOutState)
    {
        if (turnOutState == LOW)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, HIGH);
        }
        else
        {
            digitalWrite(mcForwardPin, HIGH);
            digitalWrite(mcReversePin, LOW);
        }
        digitalWrite(ledPin, turnOutState);
        previousTurnOutState = turnOutState;
    }
};
