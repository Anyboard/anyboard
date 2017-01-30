// Printer's firmware working copy
// Code based on BEAN hardware
// The bean parses json, process the text for the printer and communicates with it over serial/wired interface
// PRINTER <----serial/wired----> BEAN <---serial/BT-----> PHONE


#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"
#include <ArduinoJson.h>


//Printer variables
#define TX_PIN 5 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 4 // Arduino receive   GREEN WIRE   labeled TX on printer
SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  //Initiate serial/BT comunication with the phone
  Serial.begin(57600);
  Serial.setTimeout(25);

  //Initiate serial comunication with the printer
  mySerial.begin(19200);  // Initialize SoftwareSerial
  printer.begin();        // Init printer (same regardless of serial type)
  printer.justify('C');
  printer.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  printer.println(F("ANYBOARD printer"));
  printer.setSize('S');
  printer.println(F("Send me some JSON please..."));
  printer.feed(4);
}

void loop() {
  String payload;
  if (Serial.available() > 0)
  {
    payload = Serial.readString();
    // say what you got:
    Serial.print("I received: ");
    Serial.println(payload);
    parseJSON(payload);
    Serial.println("JSON succesfully parsed");
  }
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
  const char* text = root["string"];

  if (strcmp(device, "Printer") == 0)
  {
    if (strcmp(event, "print") == 0)
    {
      print(text);
    }
  }
}

void print(String text)
{
  printer.justify('C');
  printer.setSize('M');
  printer.println(F("NEW CARD"));
  printer.setSize('S');
  printer.println(text);
  printer.feed(4);
}


