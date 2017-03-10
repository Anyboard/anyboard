#include "Accelerometer.h"
#include "BLE_Handler.h"

// class TokenSoloEvent_Handler - Handles all the TokenSoloEvent sources (Accelerometer, Gyro, Compass...)
class TokenSoloEvent_Handler
{
    public:
      TokenSoloEvent_Handler(BLE_Handler *Handler);   //default constructor
      int pollEvent();    // If an event has occured returns the event code
    
      void setAccelerometer(Accelerometer *Acc);  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
      
    private:
      bool EventTriggered; // True if an event has occured, else false. Reset on read with pollEvent();
      int EventCode;       // Event code according to protocol.h

      BLE_Handler *BLE;
      
      //Sensors source of TokenSoloEvent
      Accelerometer *_Accelerometer; // Handle an accelerometer object
};

