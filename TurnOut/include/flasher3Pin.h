#ifndef FLASHER3PIN_H
#define FLASHER3PIN_H

#include <Arduino.h>

class flasher3Pin
{

	int ledPin1;              // the number of the first LED pin
	int ledPin2;              // the number of the second LED pin
	int buttonPin;            // the number of the button pin
	unsigned long duration;    // milliseconds of duration to flash

    int flashState;                 // which LED is currently on.ß
	unsigned long previousMillis;  	// will store last time LED was toggled

  public:
  
	flasher3Pin(int ledPin1, int ledPin2, int buttonPin, long duration);
	void update();
	
};

#endif