// Example code for tap and shake detection using accelerometer ADXL345 and RFduino

#include <Wire.h>
#include <WInterrupts.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define ACC_INT1_PIN 2 // Pin where the acceleromter interrupt1 is connected

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

volatile uint8_t intSource = 0; // byte with interrupt informations
volatile int tab[] = {'0', '0'};

void setup(void) 
{
  // Enable interrupts :
  interrupts();

  // GPIO 2 handles INT1 of the accelerometer :
  pinMode(ACC_INT1_PIN, INPUT);
  
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

  // map all interrupts in the INT1 pin
  accel.writeRegister(ADXL345_REG_INT_MAP, 0b00000000);

  /************************** Activity and Inactivity configuration **************************/
  accel.writeRegister(ADXL345_REG_THRESH_ACT, 8);
  accel.writeRegister(ADXL345_REG_THRESH_INACT, 3);
  accel.writeRegister(ADXL345_REG_TIME_INACT, 0b00000001);
  accel.writeRegister(ADXL345_REG_ACT_INACT_CTL, 0b11111111);

  /*********************** Tap and double tap configuration ************************/
  // single tap configuration
  accel.writeRegister(ADXL345_REG_DUR, 0x30); 
  accel.writeRegister(ADXL345_REG_THRESH_TAP, 0x40); 
  accel.writeRegister(ADXL345_REG_TAP_AXES, 0b001); // enable tap detection on the z axe
  
  // double tap configuration
  accel.writeRegister(ADXL345_REG_LATENT, 100);
  accel.writeRegister(ADXL345_REG_WINDOW, 255);
  /*************************************************************************************/
  
  //read and clear interrupts
  accel.readRegister(ADXL345_REG_INT_SOURCE);
}

void loop(void) 
{  
  if(digitalRead(ACC_INT1_PIN)) {
    intSource = accel.readRegister(ADXL345_REG_INT_SOURCE);
    if(bitRead(intSource, 5)) 
    {
      if(tab[1] && tab[0])
      {
        Serial.println("### Shake ");
      }
      else
      {
        Serial.println("### DOUBLE_TAP ");
      }
    }
    else if(bitRead(intSource, 6)) 
    { // when a double tap is detected also a signle tap is deteced. we use an else here so that we only print the double tap
      if(tab[1] && tab[0])
      {
        Serial.println("### Shake ");
      }
      else
      {
        Serial.println("### SINGLE_TAP ");
      }
    }
    if(bitRead(intSource, 3)) 
    {
      tab[1] = tab[0];
      tab[0] = 0;
      //Serial.println("### Inactivity ");
    }
    if(bitRead(intSource, 4)) 
    {
      tab[1] = tab[0];
      tab[0] = 1;
      //Serial.println("### Activity ");
    }
  }
  delay(300);
}
