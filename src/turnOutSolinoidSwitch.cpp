#include <Arduino.h>

class turnOutSolinoidSwitch
{
    int ledPin;            // pin that controls the 2 LEDa showing 'unthrown' and 'thrown' states
    int switchPin;         // pin for switch or DCC-EX outpit thta controls the tunrout
    int mcForwardPin;
    int mcReversePin;

    int previousTurnOutState;
    int previousSwitchState;
    unsigned long previousSwitchDownMillis;
    unsigned long previousSwitchUpMillis;
    unsigned long previousSoliniodMillis;
    unsigned long soliniodOnMillis;

    int ledOn;       // to allow LEDs common anoode or common cagthode operation
    int ledOff;      // to allow LEDs common anoode or common cagthode operation

  public:

    turnOutSolinoidSwitch ()
    {
        previousSwitchDownMillis = 0;
        previousSwitchUpMillis = 0;
        previousSoliniodMillis = 0;
        soliniodOnMillis = 20;
    }

    void setLedPin(int _ledPin)
    {
        ledPin = _ledPin;
        pinMode(ledPin, OUTPUT); 
    }

    void setSwitchPin(int _switchPin)
    {
        switchPin = _switchPin;
        pinMode(switchPin, INPUT_PULLUP);
        previousSwitchState = !(digitalRead(switchPin));
        previousTurnOutState = !(previousSwitchState);
    }

    void setSolinoidPins(int _mcForwardPin,
                         int _mcReversePin)
    {
        mcForwardPin = _mcForwardPin;
        mcReversePin = _mcReversePin;

        pinMode(mcForwardPin, OUTPUT); 
        pinMode(mcReversePin, OUTPUT); 

        digitalWrite(mcForwardPin, LOW);
        digitalWrite(mcReversePin, LOW);
    }

    void setSoliniodOnTime(unsigned long _soliniodOnMillis)
    {
        soliniodOnMillis = _soliniodOnMillis;
        if (soliniodOnMillis > 500)
        {
            soliniodOnMillis = 500;
        }
    }

    void swapLedPolarities()
    {
        ledOn = !(ledOn);
        ledOff = !(ledOff);
    }

    void loop()
    {
        unsigned long currentMillis = millis();

        // We don't want the solinoid powered for more than about 20 milliseconds to avoid damaging it
        if (currentMillis - previousSoliniodMillis >= soliniodOnMillis)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, LOW);
        }

        int currentSwitchState = digitalRead(switchPin);

        // Ignore any additional changes after a switch change - "debounce"
        if (currentMillis - previousSwitchDownMillis >= 100 && currentMillis - previousSwitchUpMillis >= 100 )
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

private:

    void activateSolinoid(int turnOutState)
    {
        if (turnOutState == LOW)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, HIGH);
            digitalWrite(ledPin, ledOn);
        }
        else
        {
            digitalWrite(mcForwardPin, HIGH);
            digitalWrite(mcReversePin, LOW);
            digitalWrite(ledPin, ledOff);
        }
        previousTurnOutState = turnOutState;
    }
};
