#include "ColorSensor.h"

ColorSensor::ColorSensor()
{
    Red = Green = Blue = 0;
    Clear = 0;
    ColorTemp = 0;
    FIR_BatterySample = 0;

    //Configuring ADC to read VCC
    analogReference(VBG); // Sets the Reference to 1.2V band gap           
    analogSelection(VDD_1_3_PS);  //Selects VDD with 1/3 prescaling as the analog source
  
    for(int i = 0; i < FIR_BATTERY_SAMPLES; i++)    // Initialisation à 0.0V
    {
      FIR_Battery[i] = 0;
    }
    
    if(!rgb_sensor.begin())
    {
        Serial.println("TCS34725 not responding...");
        while(1);
    }
}

void ColorSensor::RefreshValues() // This function has to be adapted to the current used sensor
{
  
    // Filtering Battery Voltage
    int sensorValue = analogRead(1); // the pin has no meaning, it uses VDD pin
    long batteryVoltage = (sensorValue * 360) / 1023; // convert value to voltage
    
    if(FIR_BatterySample+1 >= FIR_BATTERY_SAMPLES)
    {
       FIR_BatterySample = 0;
    }
    
    FIR_Battery[FIR_BatterySample] = batteryVoltage;
    FIR_BatterySample++;
    
    for(uint8_t i = 0; i < FIR_BATTERY_SAMPLES; i++)
    { 
        BatteryFiltered += FIR_Battery[i];
    }
    
    BatteryFiltered /= FIR_BATTERY_SAMPLES;  

    rgb_sensor.getData();
    
    Red = rgb_sensor.r / rgb_sensor.againx;
    Green = rgb_sensor.g / rgb_sensor.againx;
    Blue = rgb_sensor.b / rgb_sensor.againx;
    
    
    float CorrectionFactor = getCorrectionFactor(BatteryFiltered);
    
    ColorTemp = (Blue*35) / Red;    // 35 is completly arbitrary, fallen from the sky
    Clear = rgb_sensor.c/rgb_sensor.againx /35;
    Clear *= CorrectionFactor;
    
    #ifdef LOG_TCS
    Serial.print("C");Serial.println(ColorTemp);
    Serial.print("U");Serial.println(Clear);
    Serial.print("R");Serial.println(Red);
    Serial.print("G");Serial.println(Green);
    Serial.print("B");Serial.println(Blue);
    Serial.print("S");Serial.println(rgb_sensor.againx);
    #endif
    #ifdef LOG_BATTERY
    Serial.print("V");Serial.println(BatteryFiltered, DEC);
    #endif
}

float ColorSensor::getCorrectionFactor(long BatteryVoltage)
{
    int Index = 0;

    if(BatteryVoltage > 365)
      return float(CorrectionFactor[0]) /10000.0;

    else if(BatteryVoltage < 250)
      return float(CorrectionFactor[CorrectionFactor_NB_Samples -1]) /10000.0;
      
    for(int i = 365; BatteryVoltage - i < 0; i--)
    {
        Index++;  
    }

    return float(CorrectionFactor[Index]) /10000.0;
}

