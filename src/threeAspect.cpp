#include <Arduino.h>

class threeAspect
{

	int ledPinGreen;       // the number of the Green LED pin
    int ledPinYellow;      // the number of the Yellow LED pin
    int ledPinRed;         // the number of the Red LED pin

  public:

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

    void setGreen() 
    {
        digitalWrite(ledPinGreen, LOW);
        digitalWrite(ledPinYellow, HIGH);
        digitalWrite(ledPinRed, HIGH);
    }

    void setYellow() 
    {
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinYellow, LOW);
        digitalWrite(ledPinRed, HIGH);
    }

    void setRed() 
    {
        digitalWrite(ledPinGreen, HIGH);
        digitalWrite(ledPinYellow, HIGH);
        digitalWrite(ledPinRed, LOW);
    }

};