#include <Arduino.h>

class turnOutSolinoidFacia
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

    turnOutSolinoidFacia (int _ledPin, int _buttonPin, int _mcForwardPin, int _mcReversePin)
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
        previousButtonDownMillis = 0;
        previousButtonUpMillis = 0;
        previousSoliniodMillis = 0;
    }

    void update()
    {
        unsigned long currentMillis = millis();

        // We don't want the solinoid powered for more
        // than about 1/5 second to avoid damading it
        if (currentMillis - previousSoliniodMillis >= 20)
        {
            digitalWrite(mcForwardPin, LOW);
            digitalWrite(mcReversePin, LOW);
        }

        // Ignore any additional button movement
        // for a bit - "debounce"
        if (currentMillis - previousButtonDownMillis >= 400 && currentMillis - previousButtonUpMillis >= 400 )
        {
            int currentButtonState = digitalRead(buttonPin);
            // Filter out a long button press
            if (currentButtonState == HIGH)
            {
                previousButtonState = HIGH;
                previousButtonUpMillis = currentMillis;
            }
            // If button is low and was high 
            // before, this is new (and valid) button press
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
