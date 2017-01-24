# AnyDeck

This repository contains firmware, electronic schematics and case construction files for anyDeck

![printer front](imgs/printer.jpg)

## Demo Application
See [anyDeck demo app](../games/demo-anyDeck) for a simple demonstrator of the capabilities of AnyPawn.

## Fundamentals

aDeck is an interactive version of the card deck commonly found in board games. Instead of holding stacks of cards, aDeck prints out its own cards using a small thermal printer.


AnyDeck provides visual feedbacks as listed in Table. Digital feedbacks commands are exchanged between anyDeck and the smartphone running anyboardJS using a binary protocol using. Mapping between events/feedbacks names and the binary codes is provided [here][].

- The first byte describes the type of event or digital feedback (command)
- The following bytes encode either a text string, ID for a icon or text to be encoded in a barcode

| Type | Feedback | Description | Sample mapping with game mechanics | Implemented ? |
|------|----------|-------------|------------------------------------|---------------|
|Visual | CARD[text] | A new card with textual information is printed | Inform the player about an event | yes |
| | CARD[icon] | A new card with an graphical icon is printed | Represent a resource that the player owns | no |
|	| CARD[barcode] | A new card with a barcode is printed | Trigger an action when barcode is scanned | no |

Besides having textual and graphical information on card, aDeck can also be configured to print cards with 2D-barcodes that can be recognised by smartphone cameras or dedicated devices, and used in certain games to trigger game mechanics. This is not yet specifically addressed by our platform but can be easily implemented with third-party tools.

## Hardware
aDeck is implemented using a thermal printer capable to print on conven- tional thermal paper up to 4.8cm length, and an Arduino-compatible board.

* [Bean](http://legacy.punchthrough.com/bean/)  *This will be soon replaced by RFDUINO, same hardware as anyPawn*
* Mini Thermal Printer - [specs](https://www.adafruit.com/products/597) - [tutorial](https://learn.adafruit.com/mini-thermal-receipt-printer)
* Power adapter

## Software

### Required libraries
* Arduino IDE
* Arduino JSON - [link](https://github.com/bblanchon/ArduinoJson)
* Adafruit Thermal_Library - [link](https://github.com/adafruit/Adafruit-Thermal-Printer-Library)
