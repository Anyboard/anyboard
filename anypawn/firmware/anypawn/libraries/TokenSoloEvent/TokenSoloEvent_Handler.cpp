#include "TokenSoloEvent_Handler.h"

TokenSoloEvent_Handler::TokenSoloEvent_Handler()   //default constructor
{
    EventTriggered = false;
    EventCode = 0x00;
    _Accelerometer = NULL;
}

int TokenSoloEvent_Handler::pollEvent()    // If an event has occured returns the event code
{
    uint8_t AccEvent = 0;
    EventCode = 0;

    if(_Accelerometer != NULL)
      AccEvent = _Accelerometer->RefreshValues();

    //Mix between all sensor events (Exemple : Gyro rotated & Acc tilted = Particular event)
    EventCode = AccEvent; // Here just one sensor for the moment so no need of mixing events
    
    return EventCode;
}

void TokenSoloEvent_Handler::setAccelerometer(Accelerometer *Acc)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _Accelerometer = Acc;
}
