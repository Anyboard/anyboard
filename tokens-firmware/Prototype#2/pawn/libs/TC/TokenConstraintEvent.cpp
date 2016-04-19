/**************************************************************************
# 	NAME: TokenConstraintEvent.cpp
#	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Library which manages the Token constraint events
#
**************************************************************************/

#include "TokenConstraintEvent.h"

/**************************************************************************
#	Constructor
**************************************************************************/
TokenConstraintEvent::TokenConstraintEvent()
{
	tcs34725 rgb_sensor = tcs34725();
}

/**************************************************************************
#	Initiate the sensor
**************************************************************************/
void TokenConstraintEvent::sensorConfig()
{
	if(!rgb_sensor.begin())
	{
		Serial.println("Problem color sensor");
	}
}

/**************************************************************************
#	Receive the color temperature and the current sector ID and return the
#	new sector ID.
**************************************************************************/
uint8_t TokenConstraintEvent::locate(uint8_t current_sector_ID, float ct)
{
	if (ct==2661)
    {
		//Serial.println("Yellow");
        return 3;
    }
    else if (ct==3296)
    {
        //Serial.println("Green");
        return 4;
    }
    else if (ct==5201)
    {
        //Serial.println("Purple");
        return 5;
    }
    else if (ct==9011)
    {
		//Serial.println("Dark_blue");
        return 6;
    }
    else if (ct==7106)
    {
        //Serial.println("Light_blue");
        return 2;
    }
    else if (ct==2153)
    {
        //Serial.println("Orange");
        return 7;
    }
    else if (ct==2915)
    {
        //Serial.println("Pink");
        return 8;
    }
    else
    {
		return current_sector_ID;
        //Serial.print("Non trouve");
    }
}
