// program to test READ WRITE to SD CARD MODULE on the IoT Proto Shield Plus
// www.gtronicsShop.com

// select ARDUINO NANO or EVERY according to the device your are using
// tools->Board->"ARDUINO NANO xxxx"
// select port number

// this sketch is based on the ReadWrite example in the SD libary

#include <SPI.h>
#include <SD.h>

File myFile;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial);  // wait for serial port to connect. Needed for native USB port only
  Serial.println("***************************************************");
  Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("Gtronics.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing to file Gtronics.txt...");
    myFile.println("www.gtronicsShop.com - this line has been written by IoTPSP_SD_CARD_RW_NANO example");
    // close the file:
    myFile.close();
    Serial.println("Writing succesfully DONE!");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Gtronics.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("Gtronics.txt");
  if (myFile) {
    Serial.println("Opening file Gtronics.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
    Serial.println("reading succesfully DONE!");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Gtronics.txt");
  }
  Serial.println("***************************************************");
}

void loop() {
  // nothing happens after setup
}
