// Token's firmware working copy
// Code based on RFDUINO hardware, uses C char arrays 

#include <ArduinoJson.h>
#include <RFduinoBLE.h>

int led_green = 0;
int led_red = 1;
int led_blue = 2;

//Test JSON strings
char OFF[]= "{\"device\":\"LED\",\"event\":\"off\"}";
char GREEN[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"green\"}";
char RED[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"red\"}";
char BLUE[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"blue\"}";
char WHITE[] = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"white\"}";

void setup() {
  //Serial.begin(9600); //Streams debug messagges over the serial port DEFAULT: OFF
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
}

void loop() {

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

  if(strcmp(device, "LED") == 0)
  {
    if(strcmp(event, "on") == 0)
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
void ledOFF(){
  digitalWrite(led_red, LOW);
  digitalWrite(led_green, LOW);
  digitalWrite(led_blue, LOW);
}

// Turns on the LED on a specific color: r=red, g=gree, osv..
void ledON(char sel){
  switch(sel)
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
