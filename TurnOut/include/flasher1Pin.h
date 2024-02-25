#ifndef FLASHER1PIN_H
#define FLASHER1PIN_H

#include <Arduino.h>

class flasher1Pin
{

	int ledPin;               // the number of the LED pin
	unsigned long onTime;     // milliseconds of on-time
	unsigned long offTime;    // milliseconds of off-time

	int ledState;             	    // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  public:
  
	flasher1Pin(int pin, long on, long off);
	void update();
	
};

#endif