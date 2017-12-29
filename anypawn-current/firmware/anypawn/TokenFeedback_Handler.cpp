#include "TokenFeedback_Handler.h"

TokenFeedback_Handler::TokenFeedback_Handler()
{
    HapticAvailable = false;
    RGB_LEDAvailable = false;
    MatrixAvailable = false;
}

String TokenFeedback_Handler::UpdateFeedback()
{
    if(HapticAvailable)
      HapticMotor->RefreshValues();

    if(MatrixAvailable)
      Matrix->RefreshValues();
      
    if(RGB_LEDAvailable)
      LED->RefreshValues();
}

void TokenFeedback_Handler::HandleTime(unsigned int ElapsedTime)
{
    if(HapticAvailable)
      HapticMotor->HandleTime(ElapsedTime);

    if(MatrixAvailable)
      Matrix->HandleTime(ElapsedTime);
      
    if(RGB_LEDAvailable)
      LED->HandleTime(ElapsedTime);
} 

void TokenFeedback_Handler::setHapticMotor(Haptic *pHapticMotor)
{
    HapticMotor = pHapticMotor;
    HapticAvailable = true;
}

void TokenFeedback_Handler::Vibrate(unsigned int Time)
{  
    if(HapticAvailable == false)
      return;
      
    HapticMotor->Vibrate(Time);
}

void TokenFeedback_Handler::Vibrate(String Type)
{
    if(HapticAvailable == false)
      return;
      
    if(Type == String("short"))
      HapticMotor->VibrateShort();
    else if(Type == String("long"))
      HapticMotor->VibrateLong();
}


bool TokenFeedback_Handler::isVibrating()
{
    return HapticMotor->getState();
}


void TokenFeedback_Handler::setRGB_LED(RGB_LED *pLED)
{
    LED = pLED;
    RGB_LEDAvailable = true;
}

void TokenFeedback_Handler::parseColorString(String color, int& red, int& green, int& blue)
{
  unsigned int colorHex = strtol(&color[0], NULL, 16);
  red = (int)((colorHex >> 16) & 0xFF);  // Extract the RR byte
  green = (int)((colorHex >> 8) & 0xFF); // Extract the GG byte
  blue = (int)((colorHex) & 0xFF);       // Extract the BB byte
}

void TokenFeedback_Handler::setColor(String color)
{
  if (color == "off")
    LED->setRGBaColor(0, 0, 0);
  else if (color == "red")
    LED->setRGBaColor(255, 0, 0);
  else if (color == "green")
    LED->setRGBaColor(0, 255, 0);
  else if (color == "blue")
    LED->setRGBaColor(0, 0, 255);
  else if (color == "white")
    LED->setRGBaColor(255, 255, 255);
  else if (color.length() == 6)
  {
    int red, green, blue;
    parseColorString(color, red, green, blue);
    LED->setRGBaColor(red, green, blue);
  }
}


void TokenFeedback_Handler::BlinkLED(unsigned int pBlinkingTime, unsigned int pBlinkingPeriod)
{
    LED->Blink(pBlinkingTime, pBlinkingPeriod);
}

void TokenFeedback_Handler::setMatrix8x8(Matrix8x8 *pMatrix)
{
    if(pMatrix->Available)
    {
      MatrixAvailable = true;
      Matrix = pMatrix;
    }

    else
      MatrixAvailable = false;
}

void TokenFeedback_Handler::DisplayDigit(int Digit, int Time)
{
    if(MatrixAvailable)
      Matrix->DisplayDigit(Digit, Time);
}

void TokenFeedback_Handler::DisplayPattern(uint8_t *Pattern)
{
    Matrix->setPattern(0, Pattern);
    Matrix->DisplayPattern(0);
}

