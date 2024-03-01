#include <Arduino.h>

class flashOneLed
{

	int ledPin;               // the number of the LED pin
	unsigned long onTime;     // milliseconds of on-time
	unsigned long offTime;    // milliseconds of off-time

	int ledState;             	    // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  public:
  
    flashOneLed(int _ledPin, long _onTime, long _offTime)
    {
        ledPin = _ledPin;
        pinMode(ledPin, OUTPUT);     
        
        onTime = _onTime;
        offTime = _offTime;
        
        ledState = LOW; 
        previousMillis = 0;
    }

    void update()
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