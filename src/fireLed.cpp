#include <Arduino.h>

// LED Fire Effect
// Wire up 3 LED's. Use 2 x Diffused Yellow and 1 x Diffused RED

class fireLed
{

    int ledPin1;
    int ledPin2;
    int ledPin3;

    unsigned long flickerTime;     // milliseconds of on-timeß
    unsigned long previousMillis;  // will store last time LED was updated

  public:
  
    fireLed()
    {  
        flickerTime = 100;
        previousMillis = 0;
    }

    void setLedPin1(int _ledPin1)
    {
        ledPin1 = _ledPin1;
        pinMode(ledPin1, OUTPUT);
    }

    void setLedPin2(int _ledPin2)
    {
        ledPin2 = _ledPin2;
        pinMode(ledPin2, OUTPUT);
    }

    void setLedPin3(int _ledPin3)
    {
        ledPin3 = _ledPin3;
        pinMode(ledPin3, OUTPUT);
    }

    void loop() {

        // check to see if it's time to change the state of the LED
        unsigned long currentMillis = millis();

        if(currentMillis - previousMillis >= flickerTime) {

            analogWrite(ledPin1, random(120)+135);
            analogWrite(ledPin2, random(120)+135);
            analogWrite(ledPin3, random(120)+135);

            previousMillis = currentMillis;   // Remember the time
        }

    }

private:


};

