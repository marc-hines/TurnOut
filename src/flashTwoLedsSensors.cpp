#include <Arduino.h>

class flashTwoLedsSensors
{

	int ledPin1;               // the number of the first LED pin
	int ledPin2;               // the number of the second LED pin
	int sensor1Pin;            // the number of the first sensor pin
	int sensor2Pin;            // the number of the second sensor pin
    int sensor3Pin;            // the number of the third sensor pin
    int sensor4Pin;            // the number of the fourth sensor pin
	unsigned long duration;    // milliseconds of duration to flash
    unsigned long delay;       // milliseconds of delay to end flashing

    int flashingState;
    int ledOneState;                        // which LED is currently on.
    int previousSensor1State;               // Allows tracking if the senor 1 state has changed
    int previousSensor2State;               // Allows tracking if the senor 2 state has changed
    int previousSensor3State;               // Allows tracking if the senor 3 state has changed
    int previousSensor4State;               // Allows tracking if the senor 4 state has changed
	unsigned long previousLedChangedMillis; // will store last time LED was toggled
    unsigned long flashLedsUntilMillis;     // will store last time LED was toggled

  public:
  
    flashTwoLedsSensors(int _ledPin1, 
                        int _ledPin2,
                        int _sensor1Pin,
                        int _sensor2Pin,
                        int _sensor3Pin,
                        int _sensor4Pin,
                        unsigned long _duration,
                        unsigned long _delay)
    {
        ledPin1 = _ledPin1;
        ledPin2 = _ledPin2;
        pinMode(ledPin1, OUTPUT);
        pinMode(ledPin2, OUTPUT);
        sensor1Pin = _sensor1Pin;
        pinMode(sensor1Pin, INPUT_PULLUP);
        sensor2Pin = _sensor2Pin;
        if (sensor2Pin != 0){
            pinMode(sensor2Pin, INPUT_PULLUP);
        }
        sensor3Pin = _sensor3Pin;
        if (sensor3Pin != 0){
            pinMode(sensor3Pin, INPUT_PULLUP);
        }
        sensor4Pin = _sensor4Pin;
        if (sensor4Pin != 0){
            pinMode(sensor4Pin, INPUT_PULLUP);
        }

        duration = _duration;
        delay = _delay;

        flashingState = LOW;
        ledOneState = HIGH;
        previousSensor1State = digitalRead(sensor1Pin);
        if (sensor2Pin != 0){
            previousSensor2State = digitalRead(sensor2Pin);
        }
        if (sensor3Pin != 0){
            previousSensor3State = digitalRead(sensor3Pin);
        }
        if (sensor4Pin != 0){
            previousSensor4State = digitalRead(sensor4Pin);
        }
        previousLedChangedMillis = 0;
        flashLedsUntilMillis = 0;
    }

    void update()
    {
        unsigned long currentMillis = millis();

        int currentSensor1State = digitalRead(sensor1Pin);
        if (currentSensor1State == HIGH && previousSensor1State == LOW)
        {
            previousSensor1State = HIGH;
        }
        if (currentSensor1State == LOW && previousSensor1State == HIGH)
        {
            previousSensor1State = LOW;
            flashLedsUntilMillis =  currentMillis + delay;
        }

        if (sensor2Pin != 0){
            int currentSensor2State = digitalRead(sensor2Pin);
            if (currentSensor2State == HIGH && previousSensor2State == LOW)
            {
                previousSensor2State = HIGH;
            }
            if (currentSensor2State == LOW && previousSensor2State == HIGH)
            {
                previousSensor2State = LOW;
                flashLedsUntilMillis =  currentMillis + delay;
            }
        }

        if (sensor3Pin != 0){
            int currentSensor3State = digitalRead(sensor3Pin);
            if (currentSensor3State == HIGH && previousSensor3State == LOW)
            {
                previousSensor3State = HIGH;
            }
            if (currentSensor3State == LOW && previousSensor3State == HIGH)
            {
                previousSensor3State = LOW;
                flashLedsUntilMillis =  currentMillis + delay;
            }
        }

        if (sensor4Pin != 0){
            int currentSensor4State = digitalRead(sensor4Pin);
            if (currentSensor4State == HIGH && previousSensor4State == LOW)
            {
                previousSensor4State = HIGH;
            }
            if (currentSensor4State == LOW && previousSensor4State == HIGH)
            {
                previousSensor4State = LOW;
                flashLedsUntilMillis =  currentMillis + delay;
            }
        }

        if (currentMillis <= flashLedsUntilMillis)
        {
            // Keep the LEDs flashing
            if (currentMillis - previousLedChangedMillis >= duration)
            {
                if (ledOneState == HIGH)
                {
                    ledOneState = LOW;  // turn off first LED
                    digitalWrite(ledPin1, LOW);     // Update the actual LED1
                    digitalWrite(ledPin2, HIGH);    // Update the actual LED2
                }
                else if (ledOneState == LOW)
                {
                    ledOneState = HIGH;  // turn on First LED
                    digitalWrite(ledPin1, HIGH);    // Update the actual LED1
                    digitalWrite(ledPin2, LOW);     // Update the actual LED2
                }
                previousLedChangedMillis = currentMillis;  // Remember the time
            }
        }
        else
        {
            // Turn off both LEDs
            digitalWrite(ledPin1, LOW);     // Update the actual LED1
            digitalWrite(ledPin2, LOW);     // Update the actual LED2
        }
    }
};
