#include "TokenSoloEvent_Handler.h"

TokenSoloEvent_Handler::TokenSoloEvent_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventCode = 0x00;

    //Accelerometer
    _Accelerometer = NULL;
    Accelerometer_Timing = 0;

    //InertialCentral
    _InertialCentral = NULL;
    InertialCentral_Timing = 0;
}


void TokenSoloEvent_Handler::HandleTime(unsigned int ElapsedTime)
{
    Accelerometer_Timing += ElapsedTime;  
    InertialCentral_Timing += ElapsedTime;
    _InertialCentral->HandleTime(ElapsedTime);
}

int TokenSoloEvent_Handler::pollEvent()    // If an event has occured returns the event code
{
    uint8_t AccEvent = 0;
    uint8_t InertialCentralEvent = 0;

    if(_AccelerometerAvailable == true && Accelerometer_Timing >= ACCELEROMETER_UPDATE)
    {
        Accelerometer_Timing = 0;
        
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

    if(_InertialCentralAvailable == true && InertialCentral_Timing >= ACCELEROMETER_UPDATE)
    {
        InertialCentral_Timing = 0;
        short isRotated = _InertialCentral->isRotated();
        
        _InertialCentral->RefreshValues();
        
        if (_InertialCentral->isTapped())
            InertialCentralEvent = TAP;
        
        else if (_InertialCentral->isDoubleTapped())
            InertialCentralEvent = DOUBLE_TAP;
        
        else if (_InertialCentral->isShaked())
            InertialCentralEvent = SHAKE;
        
        else if (_InertialCentral->isTilted())
            InertialCentralEvent = TILT;
        
        else if(isRotated != 0)
        {
            if(isRotated == 1)
                InertialCentralEvent = TRIG_ROT;
            else if(isRotated == -1)
                InertialCentralEvent = A_TRIG_ROT;
        }
    }
    
    //Mix between all sensor events (Exemple : Gyro rotated & Acc tilted = Particular event)
    if(_InertialCentralAvailable == true)
      EventCode = InertialCentralEvent; 

    else if(_AccelerometerAvailable == true)
      EventCode = AccEvent; 

    else
      EventCode = 0x00;

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
    _AccelerometerAvailable = Acc->SensorAvailable;
}

void TokenSoloEvent_Handler::setInertialCentral(InertialCentral_LSM9DS0 *InC)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _InertialCentral = InC;
    _InertialCentralAvailable = InC->SensorAvailable;
}



