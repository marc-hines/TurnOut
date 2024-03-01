#include <Arduino.h>

class flashTwoLeds
{

	int ledPin1;               // the number of the first LED pin
	int ledPin2;               // the number of the second LED pin
	int buttonPin;             // the number of the button pin
	unsigned long duration;    // milliseconds of duration to flash

    int flashingState;
    int ledOneState;                 // which LED is currently on.
    int previousButtonState;
    int previousButtonDownMillis;
    int previousButtonUpMillis;
	unsigned long previousMillis;    // will store last time LED was toggled

  public:
  
    flashTwoLeds(int _ledPin1, int _ledPin2, int _buttonPin, long _duration)
    {
        ledPin1 = _ledPin1;
        ledPin2 = _ledPin2;
        buttonPin = _buttonPin;
        pinMode(ledPin1, OUTPUT);
        pinMode(ledPin2, OUTPUT); 
        pinMode(buttonPin, INPUT_PULLUP); 

        duration = _duration;

        flashingState = HIGH;
        ledOneState = HIGH; 
        previousButtonState = HIGH;
        previousButtonDownMillis = 0;
        previousButtonUpMillis = 0;
        previousMillis = 0;
    }

    void update()
    {
        unsigned long currentMillis = millis();

        int currentButtonState = digitalRead(buttonPin);

        // Ignore any additional button movement for a bit after a button press or release - "debounce"
        if (currentMillis - previousButtonDownMillis >= 400 && currentMillis - previousButtonUpMillis >= 400 )
        {
            if (currentButtonState == HIGH && previousButtonState == LOW)
            {
                previousButtonState = HIGH;
                previousButtonUpMillis = currentMillis;
                flashingState = HIGH;
            }
            if (currentButtonState == LOW && previousButtonState == HIGH)
            {
                previousButtonState = LOW;
                previousButtonDownMillis = currentMillis;
                flashingState = LOW;
            }
        }

        if (flashingState == HIGH)
        {
            // Keep the LEDs flashing
            if (currentMillis - previousMillis >= duration)
            {
                if (ledOneState == HIGH)
                {
                    ledOneState = LOW;  // turn off first LED
                    digitalWrite(ledPin1, LOW);     // Update the actual LED1
                    digitalWrite(ledPin2, HIGH);    // Update the actual LED2
                }
                else if (ledOneState == LOW)
                {
                    ledOneState = HIGH;  // turn on First LED
                    digitalWrite(ledPin1, HIGH);    // Update the actual LED1
                    digitalWrite(ledPin2, LOW);     // Update the actual LED2
                }
                previousMillis = currentMillis;  // Remember the time
            }
        }
        else
        {
            // Turn off both LEDs
            digitalWrite(ledPin1, LOW);     // Update the actual LED1
            digitalWrite(ledPin2, LOW);     // Update the actual LED2
        }
    }
};
