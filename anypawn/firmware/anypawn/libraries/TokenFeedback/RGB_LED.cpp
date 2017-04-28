#include "RGB_LED.h"

RGB_LED::RGB_LED(int pR, int pG, int pB, int Type)
{
    _R_LED = pR;
    _G_LED = pG;
    _B_LED = pB;

    pinMode(_R_LED, OUTPUT);
    pinMode(_G_LED, OUTPUT);
    pinMode(_B_LED, OUTPUT);
	
	R = G = B = 0;

	if(Type != COMMON_ANODE && Type != COMMON_CATHODE)
		_Type = COMMON_CATHODE;
	
	else
		_Type = Type;
	
	if(Type == COMMON_ANODE)
	{
		digitalWrite(_R_LED, !LED_OFF);
		digitalWrite(_G_LED, !LED_OFF);
		digitalWrite(_B_LED, !LED_OFF);
	}
	
	else
	{
		digitalWrite(_R_LED, LED_OFF);
		digitalWrite(_G_LED, LED_OFF);
		digitalWrite(_B_LED, LED_OFF);
	}

    State = LED_OFF;
}


void RGB_LED::Blink(unsigned int pBlinkingTime, unsigned int pBlinkingPeriod)
{
	Blinking = true;
	BlinkingPeriod = pBlinkingPeriod;
	BlinkingTime = pBlinkingTime;
}

void RGB_LED::setRGBaColor(uint8_t pR, uint8_t pG, uint8_t pB, float a)
{
    if(_Type == COMMON_ANODE)
	{
      R = (255 - R);
      G = (255 - G);
      B = (255 - B);
	}
    
	R = pR;
	G = pG;
	B = pB;
	
    analogWrite(_R_LED, pR);
    analogWrite(_G_LED, pG);
    analogWrite(_B_LED, pB);
}


void RGB_LED::HandleTime(unsigned int ElapsedTime)
{
	if(Blinking == true)
		RGB_LED_Timing += ElapsedTime;
}

void RGB_LED::RefreshValues()
{
    if(Blinking == true)
	{
		if(RGB_LED_Timing < BlinkingTime || BlinkingTime == 0)
		{
			if((RGB_LED_Timing / BlinkingPeriod) % 2)
			{
				State = INACTIVE;
				
				if(_Type == COMMON_ANODE)
				{
					analogWrite(_R_LED, 255);
					analogWrite(_G_LED, 255);
					analogWrite(_B_LED, 255);
				}
				
				else
				{
					analogWrite(_R_LED, 0);
					analogWrite(_G_LED, 0);
					analogWrite(_B_LED, 0);
				}
			}
			
			else
			{
				State = ACTIVE;
				
				if(_Type == COMMON_ANODE)
				{
					analogWrite(_R_LED, (255-R));
					analogWrite(_G_LED, (255-G));
					analogWrite(_B_LED, (255-B));
				}
				
				else
				{
					analogWrite(_R_LED, R);
					analogWrite(_G_LED, G);
					analogWrite(_B_LED, B);
				}
			}
		}
		
		else
		{
			State = ACTIVE;
			analogWrite(_R_LED, R);
			analogWrite(_G_LED, G);
			analogWrite(_B_LED, B);
			
			Blinking = false;
			RGB_LED_Timing = 0;
		}
	}
}

