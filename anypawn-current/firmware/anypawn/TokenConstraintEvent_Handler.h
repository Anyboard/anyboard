#ifndef TOKENCONSTRAINTEVENT_HANDLER_H
#define TOKENCONSTRAINTEVENT_HANDLER_H

// LOG
#define LOG_CONSTRAINT_EVENT
#include "ColorSensor.h"
#include "BLE_Handler.h"

class BLE_Handler;

#define LASER 1
#define INK 2
#define DMIN 4 // Distance min for Locate() function

// class TokenConstraintEvent_Handler - Handles all the TokenConstraintEvent sources (ColorSensor...)
class TokenConstraintEvent_Handler
{
    public:
      TokenConstraintEvent_Handler(BLE_Handler *Handler);   //default constructor
      void pollEvent();    // Send triggered events
      uint8_t CurrentSector_ID;
      uint8_t LastSector_ID;
      void setColorSensor(ColorSensor *Sensor);  // Set the private member _Accelerometer with an existing instance of an Accelerometer object
      void HandleTime(unsigned int ElapsedTime);
      void setPaper(int pPaper);
      
    private:
      int Paper;  
      uint8_t Locate(int ct, int cl);
      BLE_Handler *BLE;  
      //Timing
      #define COLOR_SENSOR_UPDATE   1000 // Update period in ms
      int ColorSensor_Timing; // 
      //Sensors source of TokenSoloEvent
      ColorSensor *_ColorSensor; // Handle an accelerometer object
};
#endif
