#include <Arduino.h>

class turnOutSolinoidButton
{
    int ledPin;
    int buttonPin;
    int mcForwardPin;
    int mcReversePin;

    int turnOutState;
    int previousButtonState;
    unsigned long previousButtonDownMillis;
    unsigned long previousButtonUpMillis;
    unsigned long previousSoliniodMillis;

  public:

    turnOutSolinoidButton ()
    {
        turnOutState = LOW;
        previousButtonState = HIGH;
        previousButtonDownMillis = 0;
        previousButtonUpMillis = 0;
        previousSoliniodMillis = 0;
    }

    void setLedPin(int _ledPin)
    {
        ledPin = _ledPin;
        pinMode(ledPin, OUTPUT); 
    }

    void setButtonPin(int _buttonPin)
    {
        buttonPin = _buttonPin;
        pinMode(buttonPin, INPUT_PULLUP);
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

    void loop()
    {
        unsigned long currentMillis = millis();

        // We don't want the solinoid powered for more
        // than about 20 milliseconds to avoid damaging it
        if (currentMillis - previousSoliniodMillis >= 20)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, LOW);
        }

        // Ignore any additional button movement for a bit after a button press or release - "debounce"
        if (currentMillis - previousButtonDownMillis >= 100 && currentMillis - previousButtonUpMillis >= 100 )
        {
            int currentButtonState = digitalRead(buttonPin);
            // Filter out a long button press
            if (currentButtonState == HIGH)
            {
                previousButtonState = HIGH;
                previousButtonUpMillis = currentMillis;
            }
            // If button is low and was high before, this is new (and valid) button press
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
                previousButtonDownMillis = currentMillis;
                previousSoliniodMillis = currentMillis;
                previousButtonState = LOW;
            }
        }
    }
};
