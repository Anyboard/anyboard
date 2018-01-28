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
		Serial.print("TEMP: "); Serial.print(_ColorSensor->ColorTemp);Serial.print(" CLEAR: "); Serial.println(_ColorSensor->Clear);
        
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
	if(BLE->MAC == "7d")
	{
		if (ct<=46 +1 && ct>=46 -1 && cl<=51 +DMIN && cl >=51 -DMIN)
			return 2;
		else if (ct<=53 +1 && ct>=53 -1 && cl<=59 +DMIN && cl >=59 -DMIN)
			return 5;
		else if (ct<=42 +1 && ct>=42 -1 && cl<=47 +DMIN && cl >=47 -DMIN)
			return 7;
		else if (ct<=28 +1 && ct>=28 -1 && cl<=52 +DMIN && cl >=52 -DMIN)
			return 14;
		else if (ct<=29 +1 && ct>=29 -1 && cl<=46 +DMIN && cl >=46 -DMIN)
			return 16;
		else if (ct<=26 +1 && ct>=26 -1 && cl<=49 +DMIN && cl >=49 -DMIN)
			return 18;
		else if (ct<=35 +1 && ct>=35 -1 && cl<=63 +DMIN && cl >=63 -DMIN)
			return 21;
		else if (ct<=34 +1 && ct>=34 -1 && cl<=55 +DMIN && cl >=55 -DMIN)
			return 24;
		else if (ct<=33 +1 && ct>=33 -1 && cl<=48 +DMIN && cl >=48 -DMIN)
			return 30;
		else if (ct<=19 +1 && ct>=19 -1 && cl<=67 +DMIN && cl >=67 -DMIN)
			return 31;
		else if (ct<=19 +1 && ct>=19 -1 && cl<=61 +DMIN && cl >=61 -DMIN)
			return 33;
		else if (ct<=19 +1 && ct>=19 -1 && cl<=97 +DMIN && cl >=97 -DMIN)
			return 37;
		else
		  return CurrentSector_ID;
	}
	else if(BLE->MAC == "e7"){
			if (ct<=75 +1 && ct>=75 -1 && cl<=85 +DMIN && cl >=85 -DMIN)
			return 2;
		else if (ct<=87 +1 && ct>=87 -1 && cl<=99 +DMIN && cl >=99 -DMIN)
			return 5;
		else if (ct<=69 +1 && ct>=69 -1 && cl<=78 +DMIN && cl >=78 -DMIN)
			return 7;
		else if (ct<=44 +1 && ct>=44 -1 && cl<=82 +DMIN && cl >=82 -DMIN)
			return 14;
		else if (ct<=46 +1 && ct>=46 -1 && cl<=72 +DMIN && cl >=72 -DMIN)
			return 16;
		else if (ct<=41 +1 && ct>=41 -1 && cl<=77 +DMIN && cl >=77 -DMIN)
			return 18;
		else if (ct<=57 +1 && ct>=57 -1 && cl<=101 +DMIN && cl >=101 -DMIN)
			return 21;
		else if (ct<=56 +1 && ct>=56 -1 && cl<=88 +DMIN && cl >=88 -DMIN)
			return 24;
		else if (ct<=55 +1 && ct>=55 -1 && cl<=77 +DMIN && cl >=77 -DMIN)
			return 30;
		else if (ct<=29 +1 && ct>=29 -1 && cl<=103 +DMIN && cl >=103 -DMIN)
			return 31;
		else if (ct<=30 +1 && ct>=30 -1 && cl<=93 +DMIN && cl >=93 -DMIN)
			return 33;
		else if (ct<=29 +1 && ct>=29 -1 && cl<=142 +DMIN && cl >=142 -DMIN)
			return 37;
		else
		  return CurrentSector_ID;
	} else{}

}





