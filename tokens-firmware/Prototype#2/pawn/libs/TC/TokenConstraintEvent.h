/**************************************************************************
# 	NAME: TokenConstraintEvent.h
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	Apache V2.0(cf. file license.txt in the main repository)
#
# 	Header of the library which manages the Token constraint events
#
**************************************************************************/

#ifndef TokenConstraintEvent_h
#define TokenConstraintEvent_h

#include <Arduino.h>
#include "tcs34725.h"

class TokenConstraintEvent {
      public:
		TokenConstraintEvent();
		uint8_t locate(uint8_t current_sector_ID, float ct);
		void sensorConfig();
		
		tcs34725 rgb_sensor;
	  private:
	
};

#endif
