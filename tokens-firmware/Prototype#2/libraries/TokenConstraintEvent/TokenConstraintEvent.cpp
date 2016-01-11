/**************************************************************************
# 	NAME: TokenConstraintEvent.cpp
#	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Library which manages the Token constraint events
#
**************************************************************************/

#include <TokenConstraintEvent.h>
   
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
	if (ct > 2500 && ct < 2900)
    {
		Serial.print("Yellow");
        return 3;
    }
    else if (ct > 4320 && ct < 4340)
    {
        Serial.print("Green");
        return 4;
    }
    else if (ct > 4340 && ct < 4500)
    {
        Serial.print("Purple");
        return 5;
    }
    else if (ct > 5500 && ct < 6200)
    {
		Serial.print("Dark blue");
        return 6;
    }
    else if (ct > 4000 && ct < 4100)
    {
        Serial.print("Black");
        return 2;
    }
    else
    {
		return current_sector_ID;
        //Serial.print("Non trouve");
    }
}




