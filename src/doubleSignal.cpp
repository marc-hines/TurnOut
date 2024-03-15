#include <Arduino.h>

#include "threeAspect.cpp"

class doubleSignal
{

	int ledPinUpperGreen;         // the number of the Upper Green LED pin
    int ledPinUpperYellow;        // the number of the Upper Yellow LED pin
    int ledPinUpperRed;           // the number of the Upper Red LED pin
	int ledPinLowerGreen;         // the number of the Lower Green LED pin
    int ledPinLowerYellow;        // the number of the Lower Yellow LED pin
    int ledPinLowerRed;           // the number of the Lower Red LED pin

    int sensorPinEast;            // East Sensor Pin
    int sensorPinWest;            // West Sensor Pin

    int blockPinInputEast;             // East Block Input Pin from another Auruido
    int blockPinInputWest;             // West Block Input Pin from another Auruido

    boolean blockEastOccupied;    // True if the block to the East is occupied
    boolean blockWestOccupied;    // True if the block to the West is occupied

    threeAspect threeAspectUpper;
    threeAspect threeAspectLower;

  public:
  
    doubleSignal()
    {
        blockPinInputEast = 0;          // Default to no pin set
        blockPinInputWest = 0;          // Default to no pin set
    }

    void setUpperLedPins(int _ledPinUpperGreen,
                         int _ledPinUpperYellow,
                         int _ledPinUpperRed)
    {
        threeAspectUpper.setPins(_ledPinUpperGreen, _ledPinUpperYellow, _ledPinUpperRed);
    }

    void setLowerLedPins(int _ledPinLowerGreen,
                         int _ledPinLowerYellow,
                         int _ledPinLowerRed)
    {
        threeAspectLower.setPins(_ledPinLowerGreen, _ledPinLowerYellow, _ledPinLowerRed);
    }

    void setSensorPins(int _sensorPinEast,
                       int _sensorPinWest)
    {
        sensorPinEast = _sensorPinEast;
        pinMode(sensorPinEast, INPUT);
        sensorPinWest = _sensorPinWest;
        pinMode(sensorPinWest, INPUT);
    }

    void setBlockInputPins(int _blockPinInputEast,
                           int _blockPinInputWest)
    {
        blockPinInputEast = _blockPinInputEast;
        blockPinInputWest = _blockPinInputWest;
    }


};