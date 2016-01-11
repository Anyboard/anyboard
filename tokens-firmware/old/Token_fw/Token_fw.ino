// Token's firmware working copy
// Code based on RFDUINO hardware, uses C char arrays

#include <ArduinoJson.h>
#include <RFduinoBLE.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"

int led_green = 4;
int led_red = 2;
int led_blue = 3;

//JSON test strings
char OFF[] = "{\"device\":\"LED\",\"event\":\"off\"}";
char GREEN[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"green\"}";
char RED[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"red\"}";
char BLUE[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"blue\"}";
char WHITE[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"white\"}";

/* Initialise color sensor with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();
/* Initialise color sensor with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

//Variable needed for colors to sector translation
uint16_t last_sector_ID = 0;

void setup() {
  Serial.begin(57600); //Streams debug messagges over the serial port DEFAULT: OFF
  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);

  // Test LED on startup
  parseJSON(GREEN);
  delay(300);
  parseJSON(RED);
  delay(300);
  parseJSON(BLUE);
  delay(300);
  parseJSON(WHITE);
  delay(300);
  parseJSON(OFF);
  delay(300);

  //Initialise bluetooth
  //Give unique identifier
  RFduinoBLE.advertisementData = "PawnA";
  //Start the BLE stack
  RFduinoBLE.begin();

  //Start the color sensor
  if (tcs.begin()) {
    Serial.println("DEBUG: Color sensor sucesfully initiated");
  } else {
    Serial.println("DEBUG: Color sensor error");
    while (1);
  }
}

void loop() {

  //Read color codes, based on the code in https://learn.adafruit.com/adafruit-color-sensors/programming
  uint16_t r, g, b, color, colorTemp, lux;
  tcs.getRawData(&r, &g, &b, &color);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  Serial.print("DEBUG: Color: "); Serial.print(color, DEC); Serial.print(" ");
  Serial.println(" ");

  //Color hex translation to sector IDs
  // Sector_NAMES 	Sector_ID	                Color_ID (approx value given by the sensor)
  // START	 		1			12228
  // STOP	 		2			5737
  // A				3			18330
  // B				4			9560
  // C				5			8550
  // D				6			6806
  // E				7			5920
  // F				8			15454

   uint16_t current_sector_ID = 0;

  if (color > 12000 && color < 13000)
    current_sector_ID = 1;
  else if (color > 5300 && color < 5800)
    current_sector_ID = 2;
  else if (color > 18000 && color < 19000)
    current_sector_ID = 3;
  else if (color > 9000 && color < 10000)
    current_sector_ID = 4;
  else if (color > 8000 && color < 9000)
    current_sector_ID = 5;
  else if (color > 6500 && color < 7500)
    current_sector_ID = 6;
  else if (color > 5801 && color < 6300)
    current_sector_ID = 7;
  else if (color > 15000 && color < 16000)
    current_sector_ID = 8;


  //Sends sectors ID of the sector that has been left and the sector that has been reached in formatted JSON
  if (current_sector_ID != last_sector_ID)
  {
    String closure = "\"}";

    String sector_left = String("{\"event\":\"left\",\"SECTOR_ID\":\"" + last_sector_ID);
    sector_left = String(sector_left + closure);

    String sector_reached = String("{\"event\":\"reached\",\"SECTOR_ID\":\"" + current_sector_ID);
    sector_reached = String(sector_reached + closure);

    char payload1[34];
    char payload2[34];
    sector_left.toCharArray(payload1, 33);
    sector_reached.toCharArray(payload2, 33);
    
    RFduinoBLE.send(*payload1);
    RFduinoBLE.send(*payload2);
    
    //Update sector_ID variables
    last_sector_ID = current_sector_ID;
  }

  delay(10);
}


void RFduinoBLE_onAdvertisement()
{
}

void RFduinoBLE_onConnect()
{
}

void RFduinoBLE_onDisconnect()
{
}

void RFduinoBLE_onReceive(char *data, int len)
{
  parseJSON(data);
}

//Parses JSON messages
void parseJSON(char *payload) {
  char sel;
  // char json[200];
  // payload.toCharArray(json, 50);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(payload);

  // Serial.print("DEBUG: "); Serial.println(json);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }

  const char* device = root["device"];
  const char* event = root["event"];
  const char* color = root["color"];

  if (strcmp(device, "LED") == 0)
  {
    if (strcmp(event, "on") == 0)
    {
      sel = color[0];
      ledON(sel);
    }
    if (strcmp(event, "off") == 0)
    {
      ledOFF();
    }
  }
}

// Turns the LED off
void ledOFF() {
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_blue, LOW);
}

// Turns on the LED on a specific color: r=red, g=gree, osv..
void ledON(char sel) {
  switch (sel)
  {
    case 'r':
      {
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, LOW);
        Serial.println("DEBUG: LED RED ON");
        break;
      }
    case 'g':
      {
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, LOW);
        Serial.println("DEBUG: LED GREEN ON");
        break;
      }
    case 'b':
      {
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, HIGH);
        Serial.println("DEBUG: LED BLUE ON");
        break;
      }
    case 'w':
      {
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, HIGH);
        Serial.println("DEBUG: LED WITHE ON");
        break;
      }
  }
}
