// program to test SD CARD MODULE on the IoT Proto Shield Plus
// www.gtronicsShop.com

// for additional useful info check the following links:
// https://www.arduino.cc/en/reference/SD
// https://www.arduino.cc/en/Reference/SDCardNotes
// https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390

// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number
 
// this sketch is based on the CardInfo example in the SD libary

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("GTRONICS.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to GTRONICS.txt...");
    myFile.println("www.gtronicsShop.com - this line has been written by IoTPSP_SD_CARD_RW_ESP8266 example");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening GTRONICS.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("GTRONICS.txt");
  if (myFile) {
    Serial.println("GTRONICS.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening GTRONICS.txt");
  }
}

void loop() {
  // nothing happens after setup
}
