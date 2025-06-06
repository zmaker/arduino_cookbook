/*
https://github.com/schreibfaul1/ESP32-audioI2S
*/

#include "Arduino.h"
#include "Audio.h"
#include "SD.h"
#include "FS.h"

#define SD_CS     5
#define SPI_MOSI  23
#define SPI_MISO  19
#define SPI_SCK   18

#define I2S_DOUT  12
#define I2S_BCLK  13
#define I2S_LRC   14

Audio audio;

void setup() {
  Serial.begin(115200);

  pinMode(SD_CS, OUTPUT);
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  
  if (!SD.begin(SD_CS)) {
    Serial.println("Errore SD: controlla HW o formattazione");
    while(true);
  }

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(100);
  audio.connecttoFS(SD, "/sample.mp3");
}

void loop() {
  audio.loop();
}
