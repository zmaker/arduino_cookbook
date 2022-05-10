// program to test SD CARD MODULE on the IoT Proto Shield Plus
// www.gtronicsShop.com

// for additional useful info check the following links:
// https://www.arduino.cc/en/reference/SD
// https://www.arduino.cc/en/Reference/SDCardNotes
// https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390

// select ESP8266 mini board: tools->Board->"Lolin(Wemos) D1 R2 & Mini"
// select port number
 
// this sketch is based on the CardInfo example in the SD libary

// include the SD library:
#include <SPI.h>
#include <SD.h>

const int chipSelect = D8;

File root;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("\r\nWaiting for SD card to initialise...");
  if (!SD.begin(chipSelect)) { // CS is D8 in this example
    Serial.println("Initialising failed!");
    return;
  }
  Serial.println("Initialisation completed");
}

void loop(void) {
}
