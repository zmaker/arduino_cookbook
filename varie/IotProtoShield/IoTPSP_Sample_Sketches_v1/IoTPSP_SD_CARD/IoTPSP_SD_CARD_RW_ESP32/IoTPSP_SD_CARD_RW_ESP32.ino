// program to test SD CARD MODULE on the IoT Proto Shield Plus
// www.gtronicsShop.com

// for additional useful info check the example:
// File->Examples->SD(esp32)->SD_TEST
// this example is a subset of that file

// select ESP32 mini board: tools->Board->"WEMOS D1 MINI ESP32"
// select port number


#include "FS.h"
#include "SD.h"
#include "SPI.h"

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
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

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void setup() {
  Serial.begin(9600); //Serial.begin(115200);
  delay(2000);

  Serial.println();

  Serial.println("-----------------------------------");
  Serial.println("       SD CARD READ / WRITE");
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

  //create GTRONICS.txt file and write to it
  writeFile(SD, "/GTRONICS.txt", "www.gtronicsShop.com - this line has been written by IoTPSP_SD_CARD_RW_ESP32 example");

  // re-open the file for reading:
  readFile(SD, "/GTRONICS.txt");

}

void loop() {
  // nothing happens after setup
}
