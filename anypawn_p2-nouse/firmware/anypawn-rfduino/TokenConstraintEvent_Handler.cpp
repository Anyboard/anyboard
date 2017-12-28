#include "TokenConstraintEvent_Handler.h"

TokenConstraintEvent_Handler::TokenConstraintEvent_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    EventTriggered = false;
    EventCode = 0x00;
    CurrentSector_ID = LastSector_ID = 0;
    _ColorSensor = NULL;
    ColorSensor_Timing = 0;
}

void TokenConstraintEvent_Handler::HandleTime(unsigned int ElapsedTime)
{
    ColorSensor_Timing += ElapsedTime;
}

void TokenConstraintEvent_Handler::pollEvent()    // If an event has occured returns the event code
{
    if(_ColorSensor != NULL && ColorSensor_Timing >= COLOR_SENSOR_UPDATE)
    {
        ColorSensor_Timing = 0;
        
        _ColorSensor->RefreshValues();
        CurrentSector_ID = Locate(_ColorSensor->ColorTemp, _ColorSensor->Clear);
        
        if (CurrentSector_ID != LastSector_ID)
        {
            TokenEvent ConstraintEvent;
            ConstraintEvent.EventCode = MOVE;
            ConstraintEvent.Parameters[0] = CurrentSector_ID;
            ConstraintEvent.Parameters[1] = LastSector_ID;
            BLE->SendEvent(&ConstraintEvent);

            #ifdef LOG_CONSTRAINT_EVENT
            Serial.print("MOVE_TO: "); Serial.print(MOVE,DEC); Serial.print(", "); Serial.print(CurrentSector_ID,DEC); Serial.print(", "); Serial.println(LastSector_ID,DEC);
            #endif
            
            LastSector_ID = CurrentSector_ID;
        }   
    }

    return;
}



void TokenConstraintEvent_Handler::setColorSensor(ColorSensor *Sensor)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _ColorSensor = Sensor;
}


uint8_t TokenConstraintEvent_Handler::Locate(int ct, int cl)
{  
    if (ct<=70 +1 && ct>=70 -1 && cl<=90 +DMIN && cl >=90 -DMIN)
        return 2;
    else if (ct<=73 +1 && ct>=73 -1 && cl<=104 +DMIN && cl >=104 -DMIN)
        return 5;
    else if (ct<=66 +1 && ct>=66 -1 && cl<=79 +DMIN && cl >=79 -DMIN)
        return 7;
    else if (ct<=50 +1 && ct>=50 -1 && cl<=96 +DMIN && cl >=96 -DMIN)
        return 14;
    else if (ct<=45 +1 && ct>=45 -1 && cl<=105 +DMIN && cl >=105 -DMIN)
        return 15;
    else if (ct<=52 +1 && ct>=52 -1 && cl<=70 +DMIN && cl >=70 -DMIN)
        return 16;
    else if (ct<=48 +1 && ct>=48 -1 && cl<=77 +DMIN && cl >=77 -DMIN)
        return 18;
    else if (ct<=38 +1 && ct>=38 -1 && cl<=99 +DMIN && cl >=99 -DMIN)
        return 20;
    else if (ct<=58 +1 && ct>=58 -1 && cl<=112 +DMIN && cl >=112 -DMIN)
        return 21;
    else if (ct<=56 +1 && ct>=56 -1 && cl<=89 +DMIN && cl >=89 -DMIN)
        return 24;
    else if (ct<=56 +1 && ct>=56 -1 && cl<=77 +DMIN && cl >=77 -DMIN)
        return 30;
    else if (ct<=34 +1 && ct>=34 -1 && cl<=109 +DMIN && cl >=109 -DMIN)
        return 31;
    else if (ct<=39 +1 && ct>=39 -1 && cl<=91 +DMIN && cl >=91 -DMIN)
        return 33;
    else if (ct<=36 +1 && ct>=36 -1 && cl<=152 +DMIN && cl >=152 -DMIN)
        return 36;
    else if (ct<=34 +1 && ct>=34 -1 && cl<=144 +DMIN && cl >=144 -DMIN)
        return 37;
    else
      return CurrentSector_ID;
}


