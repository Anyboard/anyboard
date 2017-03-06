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

#include "protocol.h"
#include "TokenFeedback.h"
#include "TokenSoloEvent_Handler.h"
#include "TokenConstraintEvent.h"

// TOKEN FIRMWARE METADATA
#define NAME    "AnyBoard Pawn"
#define VERSION "0.1"
#define UUID    "3191-6275-32g4"


// BOARD CONSTANTS
#define ACC_INT1_PIN        4 // Pin where the acceleromter interrupt1 is connected
#define VIBRATING_M_PIN     3 // Pin where the vibrating motor is connected


// LOG 
#define   LOG_TCS

// VARIABLES FOR BLUETOOTH
uint8_t sendData[20];
uint8_t getData[20];
bool connected;
uint8_t cmd;
int i;
int len;

// Variables for Token Solo Event
TokenSoloEvent_Handler TokenSoloEvent;
Accelerometer *TokenAccelerometer;

// Variables for Token Constraint Event
uint8_t last_sector_ID = 0;
uint8_t current_sector_ID = 0;

// Initiation of the objects
TokenFeedback tokenFeedback = TokenFeedback(VIBRATING_M_PIN); // Connected on pin 2
TokenConstraintEvent tokenConstraint = TokenConstraintEvent();

void setup(void)
{
  //SERIAL INTERFACE FOR DEBUGGING PURPOSES
  Serial.begin(9600);

  // Enable interrupts :
  interrupts();

  //Initialization of the accelerometer
  TokenAccelerometer = new Accelerometer(ACC_INT1_PIN);

  // Initialization of the TokenSoloEvent_Handler
  TokenSoloEvent.setAccelerometer(TokenAccelerometer);
  
  // Config of the rgb_sensor
  tokenConstraint.sensorConfig();

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
    /************************************************************/
    // Token solo event detection
    int Event = TokenSoloEvent.pollEvent();

    if(Event != 0x00)
    {
      sendData[0] = Event;
      RFduinoBLE.send((char*) sendData, 1);
    }
    
  /************************************************************/
     // Sector detection if the token is on the board
     if (!TokenAccelerometer->isActive())
     {
       tokenConstraint.rgb_sensor.getData();
       #ifdef LOG_TCS
       Serial.print("C");Serial.println(map(tokenConstraint.rgb_sensor.ct,0,7000,0,100));
       Serial.print("R");Serial.println(tokenConstraint.rgb_sensor.r_comp);
       Serial.print("G");Serial.println(tokenConstraint.rgb_sensor.g_comp);
       Serial.print("B");Serial.println(tokenConstraint.rgb_sensor.b_comp);
       #endif
     }


     // Location of the pawn in function of the color temperature (ct)
     current_sector_ID = tokenConstraint.locate(current_sector_ID, map(tokenConstraint.rgb_sensor.ct,0,7000,0,100));
     //Serial.println(current_sector_ID);

     // Sends sectors ID of the sector that has been left and the sector that has been reached
     if (current_sector_ID != last_sector_ID)
    {
         sendData[0] = MOVE;
         sendData[1] = current_sector_ID;
         sendData[2] = last_sector_ID;
         RFduinoBLE.send((char*) sendData, 3);
         Serial.print("MOVE_TO: "); Serial.print(sendData[0],DEC); Serial.print(" , "); Serial.print(sendData[1],DEC); Serial.print(" , "); Serial.println(sendData[2],DEC);
         
         // Update sector_ID variables
         last_sector_ID = current_sector_ID;
     }
    /************************************************************/

    delay(100); // Important delay, do not delete it ! Why ?? I want to delete this one !!
}

// Code that executes everytime token is being connected to
void RFduinoBLE_onConnect()
{
  connected = true;
}

// Code that executes everytime token is being disconnected from
void RFduinoBLE_onDisconnect()
{
  connected = false;
}

// Sends data to the connected client
void send_uint8(uint8_t *data, int length)
{
  char charData[length];
  for (i = 0; i < length; i++) {
    charData[i] = data[i];
  }
  RFduinoBLE.send(charData, length);
}

// Sends data (uint8 + String) to the connected client
void send_string(uint8_t command, char* string)
{
  len = strlen(string);
  sendData[0] = command;
  for (i = 0; i < len; i++) {
    sendData[i + 1] = string[i];
  }
  send_uint8(sendData, len + 1);
}

// Code to run upon receiving data over bluetooth
void RFduinoBLE_onReceive(char *data, int length)
{
  // Stores the first integer to cmd variable
  cmd = data[0];

  // Resets the incoming data array
  memset(getData, 0, sizeof(getData));

  // Stores the rest of the incoming data in getData array
  for (i = 1; i < length; i++) {
    getData[i - 1] = data[i];
  }
  // Executes the command
  parse(cmd);
}

// Executes command
void parse(uint8_t command)
{
  // Resets the outcoming data array
  memset(sendData, 0, sizeof(sendData));

  // Sets the command as the first data to send
  sendData[0] = command;

  switch (command)
  {
    case GET_NAME:
      send_string(GET_NAME, NAME);
      break;
    case GET_VERSION:
      send_string(GET_VERSION, VERSION);
      break;
    case GET_UUID:
      send_string(GET_UUID, UUID);
      break;
    case HAS_LED:
      sendData[1] = 1;
      send_uint8(sendData, 2);
      break;
    case HAS_LED_COLOR:
      sendData[1] = 1;
      send_uint8(sendData, 2);
      break;
    case HAS_VIBRATION:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case HAS_COLOR_DETECTION:
      sendData[1] = 1;
      send_uint8(sendData, 2);
      break;
    case HAS_LED_SCREEN:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case HAS_RFID:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case HAS_NFC:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case HAS_ACCELEROMETER:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case HAS_TEMPERATURE:
      sendData[1] = 0;
      send_uint8(sendData, 2);
      break;
    case VIBRATE:
      tokenFeedback.vibrate(getData[0] * 10);
      send_uint8(sendData, 1);
      break;
    case COUNT:
      tokenFeedback.displayCount();
      send_uint8(sendData, 1);
      break;
    case DISPLAY_X:
      tokenFeedback.displayX();
      send_uint8(sendData, 1);
      break;
    case DISPLAY_W:
      tokenFeedback.displayW();
      send_uint8(sendData, 1);
      break;
    case DISPLAY_UP:
      tokenFeedback.displayUp();
      send_uint8(sendData, 1);
      break;
    case DISPLAY_DOWN:
      tokenFeedback.displayDown();
      send_uint8(sendData, 1);
      break;
    case DISPLAY_DIGIT:
      tokenFeedback.displayDigit(getData[0]);
      send_uint8(sendData, 1);
      break;
    default:
      sendData[0] = 0;
      send_uint8(sendData, 1);
  }
}
