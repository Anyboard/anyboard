/**************************************************************************
# 	NAME: TokenFeedback.h
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Header of the library which manages the Token feedbacks
#
**************************************************************************/

#ifndef Matrix_h
#define Matrix_h

#include <Arduino.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

#define ACTIVE 		true
#define INACTIVE 	false

class Matrix8x8
{
    public:
		Matrix8x8();

        void RefreshValues();
        void HandleTime(unsigned int ElapsedTime);
		void DisplayDigit(int digit, int time);
		
		void setPattern(int ID, uint8_t *Pattern);
		void DisplayPattern(int ID);
		
		bool Available;
		
	  private:
		Adafruit_8x8matrix matrix;
		
		uint8_t CustomPattern[4][8];
        unsigned int  Matrix_Timing;
		unsigned int DisplayTime;
        bool State;
		
};


static const uint8_t PROGMEM
  null_bmp[] =
  { B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000 },
  zero_bmp[] =
  { B00000000,
    B00011000,
    B00100100,
    B00100100,
    B00100100,
    B00100100,
    B00011000,
    B00000000 },
  one_bmp[] =
  { B00000000,
    B00001000,
    B00011000,
    B00101000,
    B00001000,
    B00001000,
    B00111100,
    B00000000 },
  two_bmp[] =
  { B00000000,
    B00011000,
    B00100100,
    B00000100,
    B00001000,
    B00010000,
    B00111100,
    B00000000 },
  three_bmp[] =
  { B00000000,
    B00011000,
    B00100100,
    B00001000,
    B00000100,
    B00100100,
    B00011000,
    B00000000 },
  four_bmp[] =
  { B00000000,
    B00100000,
    B00100000,
    B00101000,
    B00111100,
    B00001000,
    B00001000,
    B00000000 },
  five_bmp[] =
  { B00000000,
    B00111100,
    B00100000,
    B00111000,
    B00000100,
    B00100100,
    B00011000,
    B00000000 },
  six_bmp[] =
  { B00000000,
    B00001100,
    B00010000,
    B00111000,
    B00100100,
    B00100100,
    B00011000,
    B00000000 },
  seven_bmp[] =
  { B00000000,
    B00111100,
    B00000100,
    B00001000,
    B00010000,
    B00010000,
    B00010000,
    B00000000 },
  eight_bmp[] =
  { B00000000,
    B00011000,
    B00100100,
    B00011000,
    B00100100,
    B00100100,
    B00011000,
    B00000000 },
  nine_bmp[] =
  { B00000000,
    B00011000,
    B00100100,
    B00011100,
    B00000100,
    B00100100,
    B00011000,
    B00000000 },
  X_bmp[] =
  { B11000011,
    B11100111,
    B01111110,
    B00111100,
    B00111100,
    B01111110,
    B11100111,
    B11000011 },
  X2_bmp[] =
  { B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001 },
    W_bmp[] =
  { B10000001,
    B10000001,
    B10000001,
    B10011001,
    B01011010,
    B01011010,
    B01100110,
    B01000010
    },
    SQ_Center_bmp[] =
  { B00000000,
    B00000000,
    B00111100,
    B00111100,
    B00111100,
    B00111100,
    B00000000,
    B00000000 },
    SQ_Extern_bmp[] =
  { B11111111,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B11111111 },
    UP_bmp[] =
  { B00011000,
    B00111100,
    B01011010,
    B10011011,
    B00011000,
    B00011000,
    B00011000,
    B00011000 },
    DOWN_bmp[] =
  { B00011000,
    B00011000,
    B00011000,
    B00011000,
    B10011001,
    B01011010,
    B00111100,
    B00011000 
    };
#endif
