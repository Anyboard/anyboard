#include "TokenSoloEvent_Handler.h"

TokenSoloEvent_Handler::TokenSoloEvent_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventCode = 0x00;
    _Accelerometer = NULL;
}

int TokenSoloEvent_Handler::pollEvent()    // If an event has occured returns the event code
{
    uint8_t AccEvent = 0;

    if(_Accelerometer != NULL)
    {
        _Accelerometer->RefreshValues();
        
        if (_Accelerometer->isTapped())
            AccEvent = TAP;
        
        else if (_Accelerometer->isDoubleTapped())
            AccEvent = DOUBLE_TAP;
        
        else if (_Accelerometer->isShaked())
            AccEvent = SHAKE;
        
        else if (_Accelerometer->isTilted())
            AccEvent = TILT;
    }

    //Mix between all sensor events (Exemple : Gyro rotated & Acc tilted = Particular event)
    EventCode = AccEvent; // Here just one sensor for the moment so no need of mixing events

    if(EventCode != 0)
    {  
        TokenEvent Event;
        Event.set(EventCode);
        BLE->SendEvent(&Event);        
    }
    
    return EventCode;
}



void TokenSoloEvent_Handler::setAccelerometer(Accelerometer *Acc)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _Accelerometer = Acc;
}


