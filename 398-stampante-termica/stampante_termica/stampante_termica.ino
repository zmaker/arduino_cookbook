// https://learn.adafruit.com/mini-thermal-receipt-printer/printing-text

#include "Adafruit_Thermal.h"
#include "SoftwareSerial.h"

#define TX_PIN 6 // Arduino transmit  YELLOW WIRE  labeled RX on printer
#define RX_PIN 5 // Arduino receive   GREEN WIRE   labeled TX on printer

SoftwareSerial mySerial(RX_PIN, TX_PIN); // Declare SoftwareSerial obj first
Adafruit_Thermal printer(&mySerial);     // Pass addr to printer constructor

void setup() {
  mySerial.begin(9600);  // Initialize SoftwareSerial
  //Serial1.begin(19200); // Use this instead if using hardware serial

  printer.begin();        // Init printer (same regardless of serial type)

  printer.doubleHeightOn();
  printer.boldOn();
  printer.setSize('L');
  printer.println(F("Hello World!"));
  printer.boldOff();
  printer.doubleHeightOff();

  printer.setSize('M');
  printer.println(F("www.zeppelinmaker.it"));
  
  printer.feed(2);

  printer.sleep();      // Tell printer to sleep
  //delay(3000L);         // Sleep for 3 seconds
  //printer.wake();       // MUST wake() before printing again, even if reset
  //printer.setDefault(); // Restore printer to defaults
}

void loop() {
}
