#include <Arduino.h>
#include "flasher1Pin.h"

flasher1Pin::flasher1Pin(int _ledPin, long _onTime, long _offTime)
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
