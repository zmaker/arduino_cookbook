#include <Adafruit_NeoPixel.h>

#define MATR_PIN 10
#define MATR_X 16
#define MATR_Y 16

Adafruit_NeoPixel pixels(MATR_X * MATR_Y, MATR_PIN, NEO_GRB + NEO_KHZ800);

int x,y, dx, dy;

void setup() {
  pixels.setBrightness(50);
  pixels.begin();
  x = 4; 
  y = 0;
  dx = 2;
  dy = 1;
}

void loop() {
  pixels.clear();

  pix(x,y, pixels.Color(0,150,0));
  x = x + dx;
  if ((x >= MATR_X) || (x <= 0)) dx = -dx;
  y = y + dy;
  if ((y >= MATR_Y) || (y <= 0)) dy = -dy;
  pixels.show();
  delay(40);
}

void pix (int x, int y, uint32_t c){
  int i = (y*MATR_X) + ( (y%2) ? x : MATR_Y - 1 - x );
  pixels.setPixelColor(i, c);
}

