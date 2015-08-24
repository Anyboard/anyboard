# Anyboard

## Overall Architecture

![alt text](imgs/architecture.jpg "Overall Architecture")

Communication Protocol in use [ASCII](https://docs.google.com/spreadsheets/d/1PqcmD4IRTpB7P-OFMh9d7eEE6F2ZAORWQ02E-gsUut0/edit?usp=sharing) -  [Binary](https://docs.google.com/spreadsheets/d/1ma2AnFMcsHt9IDDLVLB10V0-0mOVHH7EsZGv8Osqqr0/edit#gid=0)

## Directory list

* Cloud - FUTURE WORK
* Phone - See [https://github.com/tomfa/anyboard-lib](https://github.com/tomfa/anyboard-lib) for current implementation
* Tokens - Work in Progress, some example tagged BEANH are based on Lightblue Bean hardware and need to be ported to RFDUINO ardure, more below..

## Token Specs (Updated August '15)

### Pawn

![pawn front](imgs/pawn1.jpg "pawn 1")
![pawn front](imgs/pawn2.jpg "pawn 2")

#### Hardware
* [RFDUINO](http://www.rfduino.com)
* RGB Color Sensor - [specs](https://www.adafruit.com/products/1356) - [tutorial](https://learn.adafruit.com/adafruit-color-sensors) 
* RGB LED
* 850Mha LiPo Battery

#### Software
* Arduino IDE
* Arduino JSON - [link](https://github.com/bblanchon/ArduinoJson)
* Color Sensor Library - [link](https://github.com/adafruit/Adafruit_TCS34725)

### Printer

![printer front](imgs/printer.jpg)

#### Hardware
* [Bean](http://legacy.punchthrough.com/bean/) *Temporaney, this will be replaced by RFDUINO*
* Mini Thermal Printer - [specs](https://www.adafruit.com/products/597) - [tutorial](https://learn.adafruit.com/mini-thermal-receipt-printer)
* Power adapter

#### Software
* Arduino IDE
* Arduino JSON - [link](https://github.com/bblanchon/ArduinoJson)
* Adafruit Thermal_Library - [link](https://github.com/adafruit/Adafruit-Thermal-Printer-Library)