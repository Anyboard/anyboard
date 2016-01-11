// Example code for tap detection using accelerometer ADXL345 and RFduino
// Single and double tap are on the same interrupt pin

#include <Wire.h>
#include <WInterrupts.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define INTERRUPT_1_ACC_PIN 2 // Pin where the acceleromter interrupt1 is connected

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

volatile uint8_t adxlIntSource = 0; // byte with interrupt informations
volatile boolean adxlTapIntState = 0; // true when an interrupt occures
volatile boolean adxlFallIntState = 0;

void setup(void) 
{
  // Enable interrupts :
  interrupts();

  // GPIO 2 handles INT1 of the accelerometer :
  pinMode(INTERRUPT_1_ACC_PIN, INPUT);
  attachPinInterrupt(INTERRUPT_1_ACC_PIN, accelInterrupt,HIGH);
  
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

  // enable single and double tap interrupt
  accel.writeRegister(ADXL345_REG_INT_ENABLE, 0b01100000);

  // map all interrupts to pin1
  accel.writeRegister(ADXL345_REG_INT_MAP, 0b00000000);

  // single tap configuration
  accel.writeRegister(ADXL345_REG_DUR, 0x30); 
  accel.writeRegister(ADXL345_REG_THRESH_TAP, 0x40); 
  accel.writeRegister(ADXL345_REG_TAP_AXES, 0b001); // enable tap detection on the z axe
  
  // double tap configuration
  accel.writeRegister(ADXL345_REG_LATENT, 0x40);
  accel.writeRegister(ADXL345_REG_WINDOW, 0xff);

  //read and clear interrupts
  accel.readRegister(ADXL345_REG_INT_SOURCE);
}

/* Tap Interrupt Routine */
int accelInterrupt(uint32_t ulPin)
{
  adxlTapIntState = 1;
  return 0;
}

void loop(void) 
{  
  adxlIntSource = accel.readRegister(ADXL345_REG_INT_SOURCE); // read the interrupt source register to reset the interrupt
  
  if (adxlTapIntState)
  {
    if(bitRead(adxlIntSource, 5)) // The 5th bit is set when double tap, the 6th is set when simple tap
    {
      Serial.println("Two taps interrupt caught");
      delay(500); // Need this to avoid the bug of detecting one tap after a double tap (the vibrate function includes it)
    }
    else
    {
      Serial.println("Singel tap interrupt caught");
    }
    
    adxlTapIntState = 0; // reset the interrupt boolean
  }
}
