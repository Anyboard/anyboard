/**************************************************************************
# 	NAME: TokenTokenEvent.cpp
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Library which manages the Token-token events
#
**************************************************************************/

#include <TokenTokenEvent.h>

/**************************************************************************
#	Constructor
**************************************************************************/
TokenTokenEvent::TokenTokenEvent()
{
	Adafruit_MPR121 cap = Adafruit_MPR121();
}

/**************************************************************************
#	Initiate the sensor
**************************************************************************/
void TokenTokenEvent::capConfig()
{
	if (!cap.begin(0x5A)) 
	{
		Serial.println("MPR121 not found, check wiring?");
		while (1);
	}
	
	delay(500);
	ref1 = cap.filteredData(6);
}

/**************************************************************************
#	Test the proximity with face1
#   !! Others functions have to be made for others faces !!
**************************************************************************/
void TokenTokenEvent::capTestProximity(int* face1)
{
	if(cap.filteredData(6) < ref1 - 12)
	{
		Serial.println("Token-Token on face 1");
		*face1 = 1;
	}
}



