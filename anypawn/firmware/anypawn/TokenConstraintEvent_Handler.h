#include "ColorSensor.h"
#include "BLE_Handler.h"

// LOG
#define LOG_CONSTRAINT_EVENT
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
      
    private:
      bool EventTriggered; // True if an event has occured, else false. Reset on read with pollEvent();
      int EventCode;       // Event code according to protocol.h
      
      uint8_t Locate(int ct, int cl);

      BLE_Handler *BLE;
      
      //Sensors source of TokenSoloEvent
      ColorSensor *_ColorSensor; // Handle an accelerometer object
};

