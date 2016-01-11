#include <Arduino.h>
#ifndef Vibrating_Motor_h
#define Vibrating_Motor_h

class Vibrating_Motor {
      public:
		Vibrating_Motor(int pin);
		void vibrate(int ms);
		void vibrateShort();
		void vibrateLong();

      private:
	  int _pin;
};

#endif
