/**************************************************************************
# 	NAME: TokenTokenEvent.h
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Header of the library which manages the Token-token events
#
**************************************************************************/

#ifndef TokenTokenEvent_h
#define TokenTokenEvent_h

#include <Arduino.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
    #define _BV(bit) (1<<(bit))
#endif

class TokenTokenEvent {
      public:
		TokenTokenEvent();
		void capConfig();
		void capTestProximity(int* face1);
		Adafruit_MPR121 cap;
		
		int ref1; // reference for the face 1
		int ref2; // reference for the face 2
		int ref3; // reference for the face 3
		int ref4; // reference for the face 4
	  private:
	
};

#endif
