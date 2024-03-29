#include <Arduino.h>

class flashOneLed
{

	int ledPin;               // the number of the LED pin
	unsigned long onTime;     // milliseconds of on-time
	unsigned long offTime;    // milliseconds of off-time

	int ledState;             	    // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  public:
  
    flashOneLed()
    {  
        onTime = 500;
        offTime = 2000;
        
        ledState = LOW; 
        previousMillis = 0;
    }

    void setLedPin(int _ledPin)
    {
        ledPin = _ledPin;
        pinMode(ledPin, OUTPUT);
    }

    void setOnDuration(int _onTime)
    {
        onTime = _onTime;
    }

    void setOffDuration(int _offTime)
    {
        offTime = _offTime;
    }

    void loop()
    {
        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();
        
        if((ledState == HIGH) && (currentMillis - previousMillis >= onTime))
        {
            swapLedState(currentMillis);
        }
        else if ((ledState == LOW) && (currentMillis - previousMillis >= offTime))
        {
            swapLedState(currentMillis);
        }
    }

private:

    void swapLedState(unsigned long currentMillis)
    {
        ledState = !(ledState);           // swap the LED state
        previousMillis = currentMillis;   // Remember the time
        digitalWrite(ledPin, ledState);	  // Update the actual LED
    }

};