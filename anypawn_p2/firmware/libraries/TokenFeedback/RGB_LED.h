/**************************************************************************
# 	NAME: TokenFeedback.h
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Header of the library which manages the Token feedbacks
#
**************************************************************************/

#ifndef RGB_LED_h
#define RGB_LED_h

#include <Arduino.h>

#define ACTIVE true
#define INACTIVE false


#define COMMON_ANODE  1
#define COMMON_CATHODE  2

#define LED_OFF LOW
#define LED_ON HIGH


class RGB_LED
{
    public:
		RGB_LED(int pR, int pG, int pB, int Type);

        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);
        
		void Blink(unsigned int pBlinkingTime, unsigned int pBlinkingPeriod);
        void setRGBaColor(uint8_t R, uint8_t G, uint8_t B, float a = 1.0);
		
	  private:
        unsigned int  RGB_LED_Timing;
        
        bool State;
		
		unsigned int BlinkingTime;
		bool Blinking;
		unsigned int BlinkingPeriod;

		uint8_t R;
		uint8_t G;
		uint8_t B;
		
        int _Type;
        int _R_LED;
        int _G_LED;
        int _B_LED;
		
};

#endif
