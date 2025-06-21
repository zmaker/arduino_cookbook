#include <Adafruit_NeoPixel.h>

#define MATR_PIN 10
#define MATR_X 16
#define MATR_Y 16

Adafruit_NeoPixel pixels(MATR_X * MATR_Y, MATR_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.setBrightness(50);
  pixels.begin();
}

void loop() {
  pixels.clear();
  for (int i = 0; i < MATR_X * MATR_Y; i++) {
    pixels.setPixelColor(i, pixels.Color(0,150,0));
    pixels.show();
    delay(50);
  }
  
}
