#include <Arduino.h>

class flasher
{
	// Class Member Variables
	// These are initialized at startup
	int ledPin;          // the number of the LED pin
	unsigned long onTime;     // milliseconds of on-time
	unsigned long offTime;    // milliseconds of off-time

	// These maintain the current state
	int ledState;             	    // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  public:
  
	flasher(int pin, long on, long off);
	void update();
	
};
