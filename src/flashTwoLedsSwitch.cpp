#include <Arduino.h>

class flashTwoLedsSwitch
{

	int ledPin1;               // the number of the first LED pin
	int ledPin2;               // the number of the second LED pin
	int switchPin;             // the number of the button pin
	unsigned long duration;    // milliseconds of duration to flash

    int flashingState;
    int ledOneState;                 // which LED is currently on.
    int previousSwitchState;
    int previousSwitchDownMillis;
    int previousSwitchUpMillis;
	unsigned long previousMillis;    // will store last time LED was toggled

  public:
  
    flashTwoLedsSwitch(int _ledPin1, int _ledPin2, int _switchPin, long _duration)
    {
        ledPin1 = _ledPin1;
        ledPin2 = _ledPin2;
        switchPin = _switchPin;
        pinMode(ledPin1, OUTPUT);
        pinMode(ledPin2, OUTPUT); 
        pinMode(switchPin, INPUT_PULLUP); 

        duration = _duration;

        flashingState = HIGH;
        ledOneState = HIGH; 
        previousSwitchState = HIGH;
        previousSwitchDownMillis = 0;
        previousSwitchUpMillis = 0;
        previousMillis = 0;
    }

    void update()
    {
        unsigned long currentMillis = millis();
        int currentButtonState = digitalRead(switchPin);

        // Ignore any additional changes after a switch change - "debounce"
        if (currentMillis - previousSwitchDownMillis >= 400 && currentMillis - previousSwitchUpMillis >= 400 )
        {
            if (currentButtonState == HIGH && previousSwitchState == LOW)
            {
                previousSwitchState = HIGH;
                previousSwitchUpMillis = currentMillis;
                flashingState = HIGH;
            }
            if (currentButtonState == LOW && previousSwitchState == HIGH)
            {
                previousSwitchState = LOW;
                previousSwitchDownMillis = currentMillis;
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
