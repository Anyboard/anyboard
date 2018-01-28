#include "tcs34725.h"
#include "CorrectionFactor.h"

#define FIR_BATTERY_SAMPLES 10

//LOG
//#define LOG_CONSTRAINT_EVENT
#ifdef LOG_CONSTRAINT_EVENT
	#define   LOG_TCS
	#define   LOG_BATTERY
#endif

class ColorSensor
{
    public:
      ColorSensor();
      int Red;  /// X acceleration instantaneous value
      int Green;  /// Y acceleration instantaneous value
      int Blue;  /// Z acceleration instantaneous value
      int Clear;
      int ColorTemp;
      void RefreshValues ();  // Reads the accelerations components

    private:
      tcs34725 rgb_sensor;  /// Object representing the used sensor    
      float getCorrectionFactor(long BatteryVoltage);
      //Variables for battery handling
      long BatteryFiltered;
      long FIR_Battery[10]; 
      int FIR_BatterySample;
};
