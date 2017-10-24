#ifndef VL6180X_H
#define VL6180X_H

#include "Adafruit_VL6180X.h"

//#define LOG_DS

#define FLOOR_DISTANCE		1
#define FLOOR_LUMINOSITY	10

class DistanceSensor
{

    public:
      DistanceSensor();
      
      int Distance;  /// X acceleration instantaneous value
      int Luminosity; /// ALS Sensor value
	  
      bool isOnFloor();
      void RefreshValues ();  // Reads the distance and clear
	  
	  bool SensorAvailable;
      
    private:
      Adafruit_VL6180X sensor;  /// Object representing the used sensor

      bool State;         // True if the sensor is active, else false
};

#endif