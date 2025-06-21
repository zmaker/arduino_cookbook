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
  pix(0,0, pixels.Color(0,150,0));
  pix(1,1, pixels.Color(150,0,0));
  pix(2,2, pixels.Color(0,0,150));

  pixels.show();
  delay(2000);
}

void pix (int x, int y, uint32_t c){
  int i = (y*MATR_X) + ( (y%2) ? x : MATR_Y - 1 - x );
  pixels.setPixelColor(i, c);
}

