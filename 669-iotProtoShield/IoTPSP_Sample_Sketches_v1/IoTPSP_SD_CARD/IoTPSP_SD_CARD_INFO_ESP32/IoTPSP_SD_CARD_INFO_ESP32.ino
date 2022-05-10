// program to test SD CARD MODULE on the IoT Proto Shield Plus
// www.gtronicsShop.com

// for additional useful info check the following links:
// https://www.arduino.cc/en/reference/SD
// https://www.arduino.cc/en/Reference/SDCardNotes
// https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number
 
// this sketch is based on the CardInfo example in the SD libary


#include "FS.h"
#include "SD.h"
#include "SPI.h"

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void setup() {
  Serial.begin(9600); //Serial.begin(115200);
  delay(2000);

  Serial.println();

  Serial.println("-----------------------------------");
  Serial.println("       READING SD CARD INFO");
  Serial.println("-----------------------------------");

  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  listDir(SD, "/", 0);
  
  Serial.println("----------------------------------");
}

void loop() {
}
