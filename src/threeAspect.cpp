#include <Arduino.h>

class threeAspect
{

	int ledPinGreen;       // the number of the Green LED pin
    int ledPinYellow;      // the number of the Yellow LED pin
    int ledPinRed;         // the number of the Red LED pin

    int ledOn;             // to allow common anoode or commonc cagthode operation
    int ledOff;            // to allow common anoode or commonc cagthode operation

  public:

    threeAspect()
    {
        setLedsCommonAnode();  // Default this 3 aspect signal to bommon anode
    }

    void setPins(int _ledPinGreen,
                 int _ledPinYellow,
                 int _ledPinRed)
    {
        ledPinGreen = _ledPinGreen;
        pinMode(ledPinGreen, OUTPUT);
        ledPinYellow = _ledPinYellow;
        pinMode(ledPinYellow, OUTPUT);
        ledPinRed = _ledPinRed;
        pinMode(ledPinRed, OUTPUT);
        setGreen();
    }

    void setLedsCommonAnode() {
        ledOn = LOW;
        ledOff = HIGH;
    }

    void setLedsCommonCathode() {
        ledOn = HIGH;
        ledOff = LOW;      
    }

    void setGreen() 
    {
        digitalWrite(ledPinGreen, ledOn);
        digitalWrite(ledPinYellow, ledOff);
        digitalWrite(ledPinRed, ledOff);
    }

    void setYellow() 
    {
        digitalWrite(ledPinGreen, ledOff);
        digitalWrite(ledPinYellow, ledOn);
        digitalWrite(ledPinRed, ledOff);
    }

    void setRed() 
    {
        digitalWrite(ledPinGreen, ledOff);
        digitalWrite(ledPinYellow, ledOff);
        digitalWrite(ledPinRed, ledOn);
    }

};