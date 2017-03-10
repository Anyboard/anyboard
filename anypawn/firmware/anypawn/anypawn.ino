/********************************************************
  # NAME: RFduino_token.ino
  # AUTHOR: Matthias Monnier (matthias.monnier@gmail.com), Simone Mora (simonem@ntnu.no)
  # DATE: 16/12/2015
  # LICENSE: Apache V2.0(cf. file license.txt in the main repository)
  #
  # Firmware of the pawn token in the AnyBoard project.
  # V01 - Removed token-token interaction, moved libraries in sketch folder
  #
********************************************************/



#include <Wire.h>
#include <WInterrupts.h>
#include <RFduinoBLE.h>
#include <string.h>

//#include "protocol.h"
#include "BLE_Handler.h"
#include "TokenFeedback.h"
#include "TokenSoloEvent_Handler.h"
#include "TokenConstraintEvent_Handler.h"


// BOARD CONSTANTS
#define ACC_INT1_PIN        4 // Pin where the acceleromter interrupt1 is connected
#define VIBRATING_M_PIN     3 // Pin where the vibrating motor is connected

// VARIABLES FOR BLUETOOTH
BLE_Handler BLE;

// Variables for Token Solo Event
TokenSoloEvent_Handler TokenSoloEvent(&BLE);
Accelerometer *TokenAccelerometer = NULL;

// Variables for Token Constraint Event
TokenConstraintEvent_Handler TokenConstraintEvent(&BLE);
ColorSensor *TokenColorSensor = NULL;

// Initiation of the objects
TokenFeedback tokenFeedback = TokenFeedback(VIBRATING_M_PIN); // Connected on pin 2


void setup(void)
{
  
  Serial.begin(9600); //SERIAL INTERFACE FOR DEBUGGING PURPOSES
  interrupts(); // Enable interrupts

  //Initialization of the Sensors
  TokenAccelerometer = new Accelerometer(ACC_INT1_PIN);
  TokenColorSensor = new ColorSensor();

  // Initialization of the TokenSoloEvent_Handler
  TokenSoloEvent.setAccelerometer(TokenAccelerometer);
  
  // Initialization of the TokenConstraintEvent_Handler
  TokenConstraintEvent.setColorSensor(TokenColorSensor);

  // Config of the LED matrix
  tokenFeedback.matrixConfig();
  
  // Configure the RFduino BLE properties
  RFduinoBLE.deviceName = "AnyPawn";
  RFduinoBLE.txPowerLevel = -20;

  // Start the BLE stack
  RFduinoBLE.begin();
  Serial.println("Setup OK!");
}

void loop(void)
{
    
    TokenSoloEvent.pollEvent();

    if (!TokenAccelerometer->isActive())
      TokenConstraintEvent.pollEvent();
    
    BLE.ProcessEvents();
    delay(100); // Important delay, do not delete it ! Why ?? I want to delete this one !!
}
