#include <Arduino.h>
//#include "../Flasher.h"
#include "../flasher.cpp"

class servoTurnOut
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
  servoTurnOut (int _ledPin, int _buttonPin, int _mcForwardPin, int _mcReversePin)
  {
    ledPin = _ledPin;
    buttonPin = _buttonPin;
    mcForwardPin = _mcForwardPin;
    mcReversePin = _mcReversePin;
    
    pinMode(ledPin, OUTPUT); 
    pinMode(buttonPin, INPUT_PULLUP); 
    pinMode(mcForwardPin, OUTPUT); 
    pinMode(mcReversePin, OUTPUT); 

    turnOutState = LOW;
    previousButtonPressMillis = 0;
    previousSoliniodMillis = 0;
  }

  void update()
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

  flasher led1(22, 200, 200);
  flasher led2(23, 200, 250);
  flasher led3(24, 200, 300);
  flasher led4(25, 200, 350);
  //flasher led5(26, 200, 400);

  //servoTurnOut turnOut1 (22,23,24,26);

void setup() {

}

void loop() {

  led1.update();
  led2.update();
  led3.update();
  led4.update();
  //led5.update();

  //servoturnOut1.update();

}
