#include "Haptic.h"
#include "RGB_LED.h"
#include "Matrix.h"


class TokenFeedback_Handler
{
    public:
      TokenFeedback_Handler();   //default constructor
      
      String UpdateFeedback();
      void HandleTime(unsigned int ElapsedTime);

      // Haptic
      void setHapticMotor(Haptic *pHapticMotor);
      void Vibrate(unsigned int Time);
      void Vibrate(String Type);
      bool isVibrating();

      // RGB Led
      void setRGB_LED(RGB_LED *pLED);
      void setColor(String color);
      void BlinkLED(unsigned int pBlinkingTime, unsigned int pBlinkingPeriod);

      // Matrix 8x8
      void setMatrix8x8(Matrix8x8 *pMatrix);
      void DisplayDigit(int Digit, int Time = 0);
      void DisplayPattern(uint8_t *Pattern);
      
    private:
      Haptic *HapticMotor;
      bool HapticAvailable;
      

      RGB_LED *LED;
      bool RGB_LEDAvailable;
      void parseColorString(String color, int& red, int& green, int& blue);

      bool MatrixAvailable;
      Matrix8x8 *Matrix;
      
};

