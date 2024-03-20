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

    int ledOn;       // to allow LEDs common anoode or common cagthode operation
    int ledOff;      // to allow LEDs common anoode or common cagthode operation

  public:

    turnOutSolinoidSwitch ()
    {
        previousSwitchDownMillis = 0;
        previousSwitchUpMillis = 0;
        previousSoliniodMillis = 0;
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

    void setLedsCommonAnode() {
        ledOn = LOW;
        ledOff = HIGH;
    }

    void setLedsCommonCathode() {
        ledOn = HIGH;
        ledOff = LOW;      
    }

    void loop()
    {
        unsigned long currentMillis = millis();

        // We don't want the solinoid powered for more than about 20 milliseconds to avoid damaging it
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
