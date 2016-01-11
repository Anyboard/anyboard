// This code tests JSON parsing for the Pawn's LED functionalities
// Code based on BEAN hardware, uses String library (dynamic memory allocation)

#include <ArduinoJson.h>

//Test JSON strings
String OFF= "{\"device\":\"LED\",\"event\":\"off\"}";
String GREEN = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"green\"}";
String RED = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"red\"}";
String BLUE = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"blue\"}";
String WHITE = "{\"device\":\"LED\",\"event\":\"on\",\"color\":\"white\"}";

void setup() {
  //Serial.begin(9600); //Streams debug messagges over the serial port DEFAULT: OFF
}

void loop() {
  // Iterates different JSON messages
  parseJSON(OFF);
  delay(1000);
  parseJSON(GREEN);
  delay(1000);
  parseJSON(RED);
  delay(1000);
  parseJSON(BLUE);
  delay(1000);
  parseJSON(WHITE);
  delay(1000);
}

//Parses JSON messages
void parseJSON(String payload) {
  char sel;
  char json[200]; 
  payload.toCharArray(json, 50);
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(json);

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
  Bean.setLed(0, 0, 0);
}

// Turns on the LED on a specific color: r=red, g=gree, osv..
void ledON(char sel){
  switch(sel)
  {
        case 'r':
    {
        Bean.setLed(255, 0, 0);
        Serial.println("DEBUG: LED RED ON");
        break;
    }
        case 'g':
    {
        Bean.setLed(0, 255, 0);
        Serial.println("DEBUG: LED GREEN ON");
        break;
    }
        case 'b':
    {
        Bean.setLed(0, 0, 255);
        Serial.println("DEBUG: LED BLUE ON");
        break;
    }
        case 'w':
    {
        Bean.setLed(255, 255, 255);
        Serial.println("DEBUG: LED WITHE ON");
        break;
    }    
  }
}
