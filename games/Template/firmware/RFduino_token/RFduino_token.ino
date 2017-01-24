/********************************************************
# NAME: RFduino_token.ino
# AUTHOR: Matthias Monnier (matthias.monnier@gmail.com)
# DATE: 16/12/2015
# LICENSE: MIT (cf. github main repository)
#
# Firmware of the pawn token in the AnyBoard project.
#
********************************************************/

#include <Wire.h>
#include <WInterrupts.h>
#include <RFduinoBLE.h>
#include <string.h>

#include <TokenFeedback.h>
#include <TokenConstraintEvent.h>
#include <TokenSoloEvent.h>
#include <TokenTokenEvent.h>

// TOKEN FIRMWARE METADATA
#define NAME    "AnyBoard Pawn"
#define VERSION "0.1"
#define UUID    "3191-6275-32g4"

// VARIABLES FOR BLUETOOTH
uint8_t sendData[20];
uint8_t getData[20];
bool connected;
uint8_t cmd;
int i;
int len;

// COMMANDS
const uint8_t GET_NAME             = 32;
const uint8_t GET_VERSION          = 33;
const uint8_t GET_UUID             = 34;
const uint8_t HAS_LED              = 64;
const uint8_t HAS_LED_COLOR        = 65;
const uint8_t HAS_VIBRATION        = 66;
const uint8_t HAS_COLOR_DETECTION  = 67;
const uint8_t HAS_LED_SCREEN       = 68;
const uint8_t HAS_RFID             = 71;
const uint8_t HAS_NFC              = 72;
const uint8_t HAS_ACCELEROMETER    = 73;
const uint8_t HAS_TEMPERATURE      = 74;
const uint8_t LED_OFF2             = 128;
const uint8_t LED_ON2              = 129;
const uint8_t LED_BLINK            = 130;
const uint8_t READ_COLOR           = 136;
const uint8_t MOVE                 = 194;
const uint8_t TTEVENT              = 195;
const uint8_t VIBRATE 			   = 200;
const uint8_t TAP				   = 201;
const uint8_t DOUBLE_TAP		   = 202;
const uint8_t SHAKE				   = 203;
const uint8_t TILT                 = 204;
const uint8_t COUNT                = 205;
const uint8_t DISPLAY_X            = 206;

// Variables for Token Solo Event
volatile uint8_t intSource = 0; // byte with interrupt informations
int tab[] = {'0', '0'};
int single_tap = 0;
int double_tap = 0;
int shake = 0;
int inactivity = 0;

// Variables for Token Constraint Event
uint8_t last_sector_ID = 0;
uint8_t current_sector_ID = 0;

// Variables for Token Token Event
int face1 = 0;

// BOARD CONSTANTS
#define ACC_INT1_PIN 4 // Pin where the acceleromter interrupt1 is connected
#define VIBRATING_M_PIN     3 // Pin where the vibrating motor is connected

// Initiation of the objects
TokenFeedback tokenFeedback = TokenFeedback(VIBRATING_M_PIN); // Connected on pin 2
TokenConstraintEvent tokenConstraint = TokenConstraintEvent();
TokenSoloEvent tokenSolo = TokenSoloEvent(ACC_INT1_PIN); // Connected on pin 4
TokenTokenEvent tokenToken = TokenTokenEvent();

void setup(void) 
{
  Serial.begin(9600);
  
  // Enable interrupts :
  interrupts();

  // Config of the rgb_sensor
  //tokenConstraint.sensorConfig();
  
  // Config of the accelerometer
  tokenSolo.accelConfig();

  // Config of the capacitive sensor
  tokenToken.capConfig();

  // Config of the LED matrix
  tokenFeedback.matrixConfig();
  
  // Configure the RFduino BLE properties
  RFduinoBLE.deviceName = "PAWN";
  RFduinoBLE.txPowerLevel = -20;

  // Start the BLE stack
  RFduinoBLE.begin();
  
  Serial.println("Setup OK!");
}
    
void loop(void) 
{  
/************************************************************/
    // Token solo event detection
    if(digitalRead(ACC_INT1_PIN)) 
    {
      intSource = tokenSolo.accel.readRegister(ADXL345_REG_INT_SOURCE);
      
      // Computation of data from the accelerometer to detect events
      tokenSolo.accelComputation(tab, bitRead(intSource, 3), bitRead(intSource, 4), bitRead(intSource, 5), bitRead(intSource, 6), &inactivity, &single_tap, &double_tap, &shake);
    }

    // Sends the events detected to the game engine
    if (single_tap) 
    {
      sendData[0] = TAP;
      RFduinoBLE.send((char*) sendData, 1);
      single_tap = 0;
    }
    else if (double_tap) 
    {
      sendData[0] = DOUBLE_TAP;
      RFduinoBLE.send((char*) sendData, 1);
      double_tap = 0;
    }
    else if (shake) 
    {
      sendData[0] = SHAKE;
      RFduinoBLE.send((char*) sendData, 1);
      shake = 0;
    }

    if(tokenSolo.tiltComputation())
    {
      Serial.println("TILT");
      sendData[0] = TILT;
      RFduinoBLE.send((char*) sendData, 1);
    }

/************************************************************/
 /*   // Sector detection if the token is on the board
    if (inactivity) 
    {
      tokenConstraint.rgb_sensor.getData();
    }
    //Serial.println(tokenConstraint.rgb_sensor.ct);

    // Location of the pawn in function of the color temperature (ct)
    current_sector_ID = tokenConstraint.locate(current_sector_ID, tokenConstraint.rgb_sensor.ct); 

    // Sends sectors ID of the sector that has been left and the sector that has been reached
    if (current_sector_ID != last_sector_ID) 
	{
        sendData[0] = MOVE;
        sendData[1] = current_sector_ID;
        sendData[2] = last_sector_ID;
        RFduinoBLE.send((char*) sendData, 3);
        
        // Update sector_ID variables
        last_sector_ID = current_sector_ID;
    }
    
/************************************************************/
    // Detection of the token token event
    tokenToken.capTestProximity(&face1); 
    if(face1==1)
    {
      Serial.println("TTEVENT");
      sendData[0] = TTEVENT;
      RFduinoBLE.send((char*) sendData, 1);
      face1 = 0;
    }
    
/************************************************************/
    delay(500); // Important delay, do not delete it !
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
        sendData[i+1] = string[i];
    }
    send_uint8(sendData, len+1);
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
        getData[i-1] = data[i];
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
            tokenFeedback.vibrate(getData[0]*10);
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
        default:
            sendData[0] = 0;
            send_uint8(sendData, 1);
    }
}
