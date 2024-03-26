#include <Arduino.h>

class twoAspect
{

	int ledPinGreen;       // the number of the Green LED pin
    int ledPinRed;         // the number of the Red LED pin

    int ledOn;             // to allow common anode or common cathode operation
    int ledOff;            // to allow common anode or common cathode operation

  public:

    twoAspect()
    {
        // Default this 2 aspect signal to common anode
        ledOn = LOW;
        ledOff = HIGH;
    }

    void setLedsCommonCathode() {
        ledOn = HIGH;
        ledOff = LOW;      
    }

    void setPins(int _ledPinGreen,
                 int _ledPinRed)
    {
        ledPinGreen = _ledPinGreen;
        pinMode(ledPinGreen, OUTPUT);
        ledPinRed = _ledPinRed;
        pinMode(ledPinRed, OUTPUT);
        setGreen();
    }

    void setGreen() 
    {
        digitalWrite(ledPinGreen, ledOn);
        digitalWrite(ledPinRed, ledOff);
    }

    void setYellow() 
    {
        digitalWrite(ledPinGreen, ledOff);
        digitalWrite(ledPinRed, ledOff);
    }

    void setRed() 
    {
        digitalWrite(ledPinGreen, ledOff);
        digitalWrite(ledPinRed, ledOn);
    }

    void setAllOff() 
    {
        digitalWrite(ledPinGreen, ledOff);
        digitalWrite(ledPinRed, ledOff);
    }

};