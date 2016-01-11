#include <Arduino.h>
#include <Vibrating_Motor.h>
   
Vibrating_Motor::Vibrating_Motor(int pin)
:_pin(pin)
{
	//Serial.println("Constructor");
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
}
  
void Vibrating_Motor::vibrate(int ms)
{
	//Serial.println("Vibrate");
	digitalWrite(_pin, HIGH);
	delay(ms);
	digitalWrite(_pin, LOW);
}

void Vibrating_Motor::vibrateShort()
{
	vibrate(500);
}

void Vibrating_Motor::vibrateLong()
{
	vibrate(1000);
}