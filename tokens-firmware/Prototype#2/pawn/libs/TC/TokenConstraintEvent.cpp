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

	if (ct<=89 && ct>=87)
    {
		//Serial.println("Light blue");
        return 0;
    }
    else if (ct<=59 && ct>=58)  //59
    {
        //Serial.println("Green");
        return 1;
    }
    else if (ct<=38 && ct>=36)
    {
        //Serial.println("Yellow");
        return 2;
    }
    else if (ct<=83 && ct>=81)
    {
		//Serial.println("blue");
        return 3;
    }
    else if (ct<=46 && ct>=44)
    {
        //Serial.println("pink");
        return 4;
    }
    else if (ct<=61 && ct>=60)
    {
        //Serial.println("purple");
        return 5;
    }
    else if (ct<=35 && ct>=33)
    {
        //Serial.println("orange");
        return 6;
    }
    else
    {
		return current_sector_ID;
        //Serial.print("Non trouve");
    }
}
