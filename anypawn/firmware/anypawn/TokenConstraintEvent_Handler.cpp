#include "TokenConstraintEvent_Handler.h"

TokenConstraintEvent_Handler::TokenConstraintEvent_Handler(BLE_Handler *Handler)   //default constructor
{
    BLE = Handler;
    CurrentSector_ID = LastSector_ID = 0;
    _ColorSensor = NULL;
    ColorSensor_Timing = 0;
	Paper = INK;
}

void TokenConstraintEvent_Handler::setPaper(int pPaper)
{
	Paper = INK;
	/*
    if(pPaper == INK || pPaper == LASER)
      Paper = pPaper;
    else
      Paper = 0; */
}

void TokenConstraintEvent_Handler::setColorSensor(ColorSensor *Sensor)  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
{
    _ColorSensor = Sensor;
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
		//Serial.print("TEMP: "); Serial.print(_ColorSensor->ColorTemp);Serial.print(" CLEAR: "); Serial.println(_ColorSensor->Clear);
        
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

uint8_t TokenConstraintEvent_Handler::Locate(int ct, int cl)
{  
	if(Paper == INK)
	{
		if (ct<=78 +1 && ct>=78 -1 && cl<=101 +DMIN && cl >=101 -DMIN)
			return 2;
		else if (ct<=83 +1 && ct>=83 -1 && cl<=114 +DMIN && cl >=114 -DMIN)
			return 5;
		else if (ct<=66 +1 && ct>=66 -1 && cl<=88 +DMIN && cl >=88 -DMIN)
			return 7;
		else if (ct<=42 +1 && ct>=42 -1 && cl<=101 +DMIN && cl >=101 -DMIN)
			return 14;
		else if (ct<=49 +1 && ct>=49 -1 && cl<=72 +DMIN && cl >=72 -DMIN)
			return 16;
		else if (ct<=41 +1 && ct>=41 -1 && cl<=83 +DMIN && cl >=83 -DMIN)
			return 18;
		else if (ct<=54 +1 && ct>=54 -1 && cl<=117 +DMIN && cl >=117 -DMIN)
			return 21;
		else if (ct<=52 +1 && ct>=52 -1 && cl<=98 +DMIN && cl >=98 -DMIN)
			return 24;
		else if (ct<=52 +1 && ct>=52 -1 && cl<=82 +DMIN && cl >=82 -DMIN)
			return 30;
		else if (ct<=28 +1 && ct>=28 -1 && cl<=116 +DMIN && cl >=116 -DMIN)
			return 31;
		else if (ct<=29 +1 && ct>=29 -1 && cl<=103 +DMIN && cl >=103 -DMIN)
			return 33;
		else if (ct<=29 +1 && ct>=29 -1 && cl<=142 +DMIN && cl >=142 -DMIN)
			return 37;
		else
		  return CurrentSector_ID;
	}
}





