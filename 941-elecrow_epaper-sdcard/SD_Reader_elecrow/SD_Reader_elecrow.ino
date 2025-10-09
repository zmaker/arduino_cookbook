// https://www.elecrow.com/wiki/CrowPanel_ESP32_E-paper_5.79-inch_HMI_Display.html#interfaces

#include <Arduino.h>  // Include the Arduino library
#include "SD.h"       // Include the SD card library
#include "EPD.h" // file display epaper

#define SD_MOSI 40    // SD card MOSI pin
#define SD_MISO 13    // SD card MISO pin
#define SD_SCK 39     // SD card SCK pin
#define SD_CS 10      // SD card CS pin

SPIClass SD_SPI = SPIClass(HSPI);

//immagine del display
uint8_t img[27200];

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("elecrow display test - sd");

  pinMode(7, OUTPUT);
  pinMode(42, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(42, HIGH);

  initDisplay();

  SD_SPI.begin(SD_SCK, SD_MISO, SD_MOSI);

  if (!SD.begin(SD_CS, SD_SPI, 80000000)) {
    Serial.println("SD KO");
  } else {
    Serial.printf("SD size: %llu \n", SD.cardSize()/(1024*1024));
    File file = SD.open("/autunno.txt");
    if (file) {

      char line[200];
      int index = 0;
      int indice_riga = 0;

      while(file.available()) {
        char c = file.read();

        if (c == '\n') {
          line[index] = '\0';
          Serial.print(line);

          EPD_ShowString(1, indice_riga*17, line, 16, BLACK);

          index = 0;
          indice_riga++;
          if (indice_riga >= 10) break;

        } else if (c == '\r') {
        } else {
          if (index < (sizeof(line)-1)) {
            line[index++] = c;
          }
        }
      }

      file.close();

      EPD_Display(img);
      EPD_PartUpdate();
      EPD_DeepSleep();

    } else {
      Serial.println("File non trovato");
    }
  }
}

void loop() {
  delay(10);
}


void initDisplay(){
  EPD_GPIOInit();
  Paint_NewImage(img, EPD_W, EPD_H, Rotation, WHITE);
  Paint_Clear(WHITE);

  EPD_FastMode1Init();
  EPD_Display_Clear();
  EPD_Update();
  EPD_Clear_R26A6H();
}
