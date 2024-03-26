#include <Arduino.h>

#include "aspects/threeAspect.cpp"

/*

[Block 1] [Block 2] [Block 3] [Block 4] [Block 5]
[s     s] [s     s] [s --> s] [s     s] [s     s]  --- Sendors in each block
          [Green--] [Red----] [Yellow-] [Green--]  <-- Signals for Opposing trains
                    [  -->  ]                      --> Train in block 3
[Green--] [Yellow-] [Red----] [Green--]            --> Signals for this train


*/


enum SIGNALSTATES
{
    SIGNAL_STATE_GREEN,
    SIGNAL_STATE_YELLOW,
    SIGNAL_STATE_RED,
};

class singleThreeAspectSignal
{
    int sensorPinBefore;           // Before Sensor Pin
    int sensorPinAfter;            // After Sensor Pin

    int blockPinInputBefore;       // Before Block Input Pin from another Auruido
    int blockPinInputAfter;        // After Block Input Pin from another Auruido

    int blockPinOutputBefore;      // Output pin to Before Block Auruido
    int blockPinOutputAfter;       // Output pin to After Block Auruido

    boolean blockBeforeOccupied;   // True if the block to the Before is occupied
    boolean blockWestOccupied;     // True if the block to the After is occupied

    threeAspect threeAspect;       // 3 aspect signal class

    SIGNALSTATES signalState;

  public:
  
    singleThreeAspectSignal()
    {
        signalState = SIGNAL_STATE_GREEN;
    }

    void setLedsCommonCathode()
    {
        threeAspect.setLedsCommonCathode();
    }

    void setLedPins(int _ledPinUpperGreen,
                    int _ledPinUpperYellow,
                    int _ledPinUpperRed)
    {
        threeAspect.setPins(_ledPinUpperGreen, _ledPinUpperYellow, _ledPinUpperRed);
    }

    void setSensorPins(int _sensorPinEast,
                       int _sensorPinWest)
    {
        sensorPinBefore = _sensorPinEast;
        pinMode(sensorPinBefore, INPUT);
        sensorPinAfter = _sensorPinWest;
        pinMode(sensorPinAfter, INPUT);
    }

    void setBlockInputPins(int _blockPinInputEast,
                           int _blockPinInputWest)
    {
        blockPinInputBefore = _blockPinInputEast;
        pinMode(blockPinInputBefore, INPUT);
        blockPinInputAfter = _blockPinInputWest;
        pinMode(blockPinInputAfter, INPUT);
    }

    void setBlockOutputPins(int _blockPinOutputEast,
                            int _blockPinOutputWest)
    {
        blockPinOutputBefore = _blockPinOutputEast;
        pinMode(blockPinOutputBefore, INPUT);
        blockPinOutputAfter = _blockPinOutputWest;
        pinMode(blockPinOutputAfter, INPUT);
    }

    void loop()
    {
        int sensorPinBeforeState = digitalRead(sensorPinBefore);
        int sensorPinAfterState = digitalRead(sensorPinAfter);

        int blockPinInputBeforeState = digitalRead(blockPinInputBefore);
        int blockPinInputAfterState = digitalRead(blockPinInputAfter);

        if (blockPinInputBeforeState == LOW)
        {
            signalState = SIGNAL_STATE_GREEN;
        }

        if (blockPinInputBeforeState == LOW)
        {
            signalState = SIGNAL_STATE_YELLOW;
        }

        if (sensorPinBeforeState == LOW)
        {
            signalState = SIGNAL_STATE_RED;
        }

        if (sensorPinBeforeState == LOW)
        {
            signalState = SIGNAL_STATE_RED;
        }

    }

};