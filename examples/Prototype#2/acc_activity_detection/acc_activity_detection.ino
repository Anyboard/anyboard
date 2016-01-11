// Example code for tap detection using accelerometer ADXL345 and RFduino
// Single and double tap are on the same interrupt pin

#include <Wire.h>
#include <WInterrupts.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define INTERRUPT_2_ACC_PIN 4 // Pin where the acceleromter interrupt1 is connected

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

volatile uint8_t actiIntSource = 0; // byte with interrupt informations
volatile boolean actiIntState = 0; // true when an interrupt occures

void setup(void) 
{
  // Enable interrupts :
  interrupts();

  // GPIO 2 handles INT1 of the accelerometer :
  pinMode(INTERRUPT_2_ACC_PIN, INPUT);
  attachPinInterrupt(INTERRUPT_2_ACC_PIN, ActivityInterrupt, HIGH);
  
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); 
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_2_G);

  // enable single and double tap interrupt + activity/inactivity interrupts
  accel.writeRegister(ADXL345_REG_INT_ENABLE, 0b01111000);

  // map activity/inactivity interrupts on int2
  accel.writeRegister(ADXL345_REG_INT_MAP, 0b00011000);

  accel.writeRegister(ADXL345_REG_THRESH_ACT, 0b00011111);
  accel.writeRegister(ADXL345_REG_THRESH_INACT, 0b00011111);
  accel.writeRegister(ADXL345_REG_TIME_INACT, 0b00000100);
  accel.writeRegister(ADXL345_REG_ACT_INACT_CTL, 0b11111111);
  
  //read and clear interrupts
  accel.readRegister(ADXL345_REG_INT_SOURCE);
}

/* Tap Interrupt Routine */
int ActivityInterrupt(uint32_t ulPin)
{
  actiIntState = 1;
  return 0;
}

void loop(void) 
{  
  
  actiIntSource = accel.readRegister(ADXL345_REG_INT_SOURCE); // read the interrupt source register to reset the interrupt
  //Serial.println(actiIntSource, BIN);
  
  if (actiIntState)
  {
    if(bitRead(actiIntSource, 4)) // The 5th bit is set when double tap, the 6th is set when simple tap
    {
      Serial.println("Activity");
      delay(500); // Need this to avoid the bug of detecting one tap after a double tap (the vibrate function includes it)
    }
    else
    {
      Serial.println("Inactivity");
      delay(500);
    }
    
    actiIntState = 0; // reset the interrupt boolean
  }
}
