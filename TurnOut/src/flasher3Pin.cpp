#include <Arduino.h>
#include "flasher3Pin.h"

flasher3Pin::flasher3Pin(int _ledPin1, int _ledPin2, int _buttonPin, long _duration)
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

  void flasher3Pin::update()
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
