/*
https://github.com/schreibfaul1/ESP32-audioI2S
*/
#include "Audio.h"
#include "WiFi.h"

#define I2S_DOUT  12
#define I2S_BCLK  13
#define I2S_LRC   14

Audio audio;

String ssid = "";
String password = "";

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("WebRadio");

  WiFi.begin(ssid.c_str(), password.c_str());
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nconnesso");

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(10); //0 - 100

  audio.connecttohost("http://vis.media-ice.musicradio.com/CapitalMP3");
}

void loop() {
  audio.loop();
}
