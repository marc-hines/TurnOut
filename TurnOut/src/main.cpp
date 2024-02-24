#include <Arduino.h>

class TurnOut
{
  int ledPin;
  int buttonPin;
  int mcForwardPin;
  int mcReversePin;

  int turnOutState;
  unsigned long previousButtonPressMillis;
  unsigned long previousSoliniodMillis;

  public:
  // Constructor
  TurnOut (int ledPinAssign, int buttonPinAssign, int mcForwardPinAssign, int mcReversePinAssign)
  {
    ledPin = ledPinAssign;
    buttonPin = buttonPinAssign;
    mcForwardPin = mcForwardPinAssign;
    mcReversePin = mcReversePinAssign;
    
    pinMode(ledPin, OUTPUT); 
    pinMode(buttonPin, INPUT_PULLUP); 
    pinMode(mcForwardPin, OUTPUT); 
    pinMode(mcReversePin, OUTPUT); 

    turnOutState = LOW;
    previousButtonPressMillis = 0;
    previousSoliniodMillis = 0;
  }

  void Update()
  {
    unsigned long currentMillis = millis();

    // We don't want the solinoid powered
    // for more than about 1/4 second.
    if (currentMillis - previousSoliniodMillis >= 250)
    {
      digitalWrite(mcForwardPin, LOW);
      digitalWrite(mcReversePin, LOW);
    }
  
    // Ignore any new button press for a bit - debounce
    if (currentMillis - previousButtonPressMillis >= 300)
    {
      // If button is low, it has been pressed
      int buttonState = digitalRead(buttonPin);
      if (buttonState == LOW )
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
        previousSoliniodMillis = currentMillis;
      }
    }
  }

};

class Flasher
{
	// Class Member Variables
	// These are initialized at startup
	int ledPin;          // the number of the LED pin
	unsigned long OnTime;     // milliseconds of on-time
	unsigned long OffTime;    // milliseconds of off-time

	// These maintain the current state
	int ledState;             		  // ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
	ledPin = pin;
	pinMode(ledPin, OUTPUT);     
	  
	OnTime = on;
	OffTime = off;
	
	ledState = LOW; 
	previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
    	ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);	  // Update the actual LED
    }
  }
};

  /**Flasher led1(22, 200, 200);
  Flasher led2(23, 200, 250);
  Flasher led3(24, 200, 300);
  Flasher led4(25, 200, 350);
  Flasher led5(26, 200, 400);**/

  TurnOut turnOut1 (22,23,24,26);

void setup() {

}

void loop() {

  /**led1.Update();
  led2.Update();
  led3.Update();
  led4.Update();
  led5.Update();**/

  turnOut1.Update();

}
