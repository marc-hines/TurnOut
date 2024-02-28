#include <Arduino.h>

class turnOutSolinoid
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

    turnOutSolinoid (int _ledPin, int _buttonPin, int _mcForwardPin, int _mcReversePin)
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

class flasher3Pin
{

	int ledPin1;              // the number of the first LED pin
	int ledPin2;              // the number of the second LED pin
	int buttonPin;            // the number of the button pin
	unsigned long duration;    // milliseconds of duration to flash

    int flashState;                 // which LED is currently on.ß
	unsigned long previousMillis;  	// will store last time LED was toggled

  public:
  
    flasher3Pin(int _ledPin1, int _ledPin2, int _buttonPin, long _duration)
    {
        ledPin1 = _ledPin1;
        ledPin2 = _ledPin2;
        buttonPin = _buttonPin;
        pinMode(ledPin1, OUTPUT);
        pinMode(ledPin2, OUTPUT); 
        pinMode(buttonPin, INPUT_PULLUP); 

        duration = _duration;

        flashState = LOW; 
        previousMillis = 0;
    }

    void update()
    {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
        
        if((flashState == HIGH) && (currentMillis - previousMillis >= duration))
        {
            flashState = LOW;  // swap states
            previousMillis = currentMillis;  // Remember the time
            digitalWrite(ledPin1, HIGH);     // Update the actual LED1
            digitalWrite(ledPin2, LOW);      // Update the actual LED2
        }
        else if ((flashState == LOW) && (currentMillis - previousMillis >= duration))
        {
            flashState = HIGH;  // turn it on
            previousMillis = currentMillis;   // Remember the time
            digitalWrite(ledPin1, LOW);      // Update the actual LED1
            digitalWrite(ledPin2, HIGH);     // Update the actual LED2
        }
    }
};

class flasher1Pin
{

	int ledPin;               // the number of the LED pin
	unsigned long onTime;     // milliseconds of on-time
	unsigned long offTime;    // milliseconds of off-time

	int ledState;             	    // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  public:
  
    flasher1Pin(int _ledPin, long _onTime, long _offTime)
    {
        ledPin = _ledPin;
        pinMode(ledPin, OUTPUT);     
        
        onTime = _onTime;
        offTime = _offTime;
        
        ledState = LOW; 
        previousMillis = 0;
    }

    void flasher1Pin::update()
    {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
        
        if((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
        {
            ledState = LOW;  // Turn it off
            previousMillis = currentMillis;  // Remember the time
            digitalWrite(ledPin, ledState);  // Update the actual LED
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
        {
            ledState = HIGH;  // turn it on
            previousMillis = currentMillis;   // Remember the time
            digitalWrite(ledPin, ledState);	  // Update the actual LED
        }
    }
};