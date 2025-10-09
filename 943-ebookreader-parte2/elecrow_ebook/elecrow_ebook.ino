// https://www.elecrow.com/wiki/CrowPanel_ESP32_E-paper_5.79-inch_HMI_Display.html#interfaces

#include <Arduino.h>  // Include the Arduino library
#include "SD.h"       // Include the SD card library
#include "EPD.h" // file display epaper

// Define the SPI pins for the SD card
#define SD_MOSI 40    // SD card MOSI pin
#define SD_MISO 13    // SD card MISO pin
#define SD_SCK 39     // SD card SCK pin
#define SD_CS 10      // SD card CS pin

SPIClass SD_SPI = SPIClass(HSPI);

//immagine del display
uint8_t img[27200];

int stato = 0;
bool FIRST = true;
uint8_t bt1, bt2, bt1_prev, bt2_prev;

String selected_file_name;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("Ebook reader p1");

  pinMode(7, OUTPUT);
  pinMode(42, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(42, HIGH);

  pinMode(2, INPUT);
  pinMode(1, INPUT);

  SD_SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
  if (!SD.begin(SD_CS, SD_SPI, 80000000)) {
    Serial.println("SD error!");
    go(99);
  }

}

void loop() {
  bt1 = digitalRead(1);
  bt2 = digitalRead(2);

  switch(stato) {
    case 0:
      initReader();
      break;
    case 1:
      chooseFile();
      break;
    case 2:
      readFile();
      break;
    case 99:
      errorState();
      break;
  }

  bt1_prev = bt1;
  bt2_prev = bt2;
}