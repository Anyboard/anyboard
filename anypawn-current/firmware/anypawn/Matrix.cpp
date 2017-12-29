#include "Matrix.h"

Matrix8x8::Matrix8x8()
{
	for(uint8_t i = 0; i < 8; i++)
	{
		CustomPattern[0][i] = 0;
		CustomPattern[1][i] = 0;
		CustomPattern[2][i] = 0;
		CustomPattern[3][i] = 0;
	}
	
	matrix.begin(0x70);
	matrix.clear();
	matrix.writeDisplay();
	
	Available = true; 
	
	State = INACTIVE;
}

void Matrix8x8::HandleTime(unsigned int  ElapsedTime)
{
	if(State != INACTIVE)
		Matrix_Timing += ElapsedTime;
}

void Matrix8x8::RefreshValues()
{
	if(DisplayTime != 0 && Matrix_Timing > DisplayTime)
	{
		matrix.clear();
		matrix.writeDisplay();
		DisplayTime = 0;
		Matrix_Timing = 0;
		State = INACTIVE;
	}
}

void Matrix8x8::setPattern(int ID, uint8_t *Pattern)
{
	for(int i = 0; i < 8; i++)
	{
		CustomPattern[ID][i] = Pattern[i];
	}
}

void Matrix8x8::DisplayPattern(int ID)
{
	matrix.clear();
	matrix.writeDisplay();
	matrix.drawBitmap(0, 0, CustomPattern[ID], 8, 8, LED_ON);
	matrix.writeDisplay();
}

void Matrix8x8::DisplayDigit(int digit, int time)
{
	
	State = ACTIVE;
	DisplayTime = time;
	
  matrix.clear();
  switch (digit) {
    case 0:
      matrix.drawBitmap(0, 0, zero_bmp, 8, 8, LED_ON);
      break;
    case 1:
      matrix.drawBitmap(0, 0, one_bmp, 8, 8, LED_ON);
      break;
    case 2:
      matrix.drawBitmap(0, 0, two_bmp, 8, 8, LED_ON);
      break;
    case 3:
      matrix.drawBitmap(0, 0, three_bmp, 8, 8, LED_ON);
      break;
    case 4:
      matrix.drawBitmap(0, 0, four_bmp, 8, 8, LED_ON);
      break;
    case 5:
      matrix.drawBitmap(0, 0, five_bmp, 8, 8, LED_ON);
      break;
    case 6:
      matrix.drawBitmap(0, 0, six_bmp, 8, 8, LED_ON);
      break;
    case 7:
      matrix.drawBitmap(0, 0, seven_bmp, 8, 8, LED_ON);
      break;
    case 8:
      matrix.drawBitmap(0, 0, eight_bmp, 8, 8, LED_ON);
      break;
    case 9:
      matrix.drawBitmap(0, 0, nine_bmp, 8, 8, LED_ON);
      break;
    default: 
      Serial.println('Not a digit');
      matrix.drawBitmap(0, 0, null_bmp, 8, 8, LED_ON);
    break;
  }
  matrix.writeDisplay();
}