/**************************************************************************
# 	NAME: TokenFeedback.cpp
# 	AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# 	DATE: 16/12/2015
# 	LICENSE: Apache V2.0(cf. file license.txt in the main repository)
#
# 	Library which manages the Token feedbacks
#
**************************************************************************/

#include "TokenFeedback.h"

/**************************************************************************
#	Constructor, receive the vibrating motor's pin
**************************************************************************/
TokenFeedback::TokenFeedback(int pin_vibrating_motor)
:_pin_motor(pin_vibrating_motor)
{
	pinMode(_pin_motor, OUTPUT);
	digitalWrite(_pin_motor, LOW);
	
	Adafruit_8x8matrix* matrix = new Adafruit_8x8matrix();
}
 
/**************************************************************************
#	Initiate the sensor
**************************************************************************/
void TokenFeedback::matrixConfig()
{
	matrix.begin(0x70);
}

/**************************************************************************
#	Receive a duration in ms, the motor vibrate during this duration
**************************************************************************/
void TokenFeedback::vibrate(int ms)
{
	//Serial.println("Vibrate");
	digitalWrite(_pin_motor, HIGH);
	delay(ms);
	digitalWrite(_pin_motor, LOW);
}

/**************************************************************************
#	Make a short vibration
**************************************************************************/
void TokenFeedback::vibrateShort()
{
	vibrate(500);
}

/**************************************************************************
#	Make a long vibration
**************************************************************************/
void TokenFeedback::vibrateLong()
{
	vibrate(1000);
}

/**************************************************************************
#	Display the digits from 0 to 9 on the screen
**************************************************************************/
void TokenFeedback::displayCount()
{
  int i;
  for(i=0; i<10; i++)
  {
    displayDigit(i);
    matrix.writeDisplay();
    delay(1000);
  }
  matrix.clear();
  matrix.writeDisplay();
  
}

/**************************************************************************
#	Display a cross on the screen
**************************************************************************/
void TokenFeedback::displayX()
{
	matrix.clear();
	matrix.drawBitmap(0, 0, X2_bmp, 8, 8, LED_ON);
	matrix.writeDisplay();
	delay(1000);
	matrix.clear();
	matrix.writeDisplay();
}
/**************************************************************************
# Display a W on the screen
**************************************************************************/
void TokenFeedback::displayW()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, W_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(5000);
  matrix.clear();
  matrix.writeDisplay();
}
/**************************************************************************
# Display a arrow up on the screen
**************************************************************************/
void TokenFeedback::displayUp()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, UP_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);
  matrix.clear();
  matrix.writeDisplay();
}
/**************************************************************************
# Display a down arrow on the screen
**************************************************************************/
void TokenFeedback::displayDown()
{
  matrix.clear();
  matrix.drawBitmap(0, 0, DOWN_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(3000);
  matrix.clear();
  matrix.writeDisplay();
}

/**************************************************************************
#	Display the argument digit on the screen
**************************************************************************/
void TokenFeedback::displayDigit(int digit)
{
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