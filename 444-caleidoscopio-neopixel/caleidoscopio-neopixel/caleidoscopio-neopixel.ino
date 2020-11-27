#include <FastLED.h>

#define N_NPIX 8
CRGB leds[N_NPIX];

void setup() {
  clearleds();
  randomSeed(analogRead(A0));
}

int hue;

void loop() {
  for (int i = 0; i < N_NPIX; i++) {
    hue = random(256);
    leds[i].setHSV( hue, 255, 127);
  }
  FastLED.show();
  delay(200);  
}

void clearleds() {
  FastLED.addLeds<WS2812, 2, GRB>(leds, N_NPIX);
  for (int i = 0; i < N_NPIX; i++) {
    leds[i] = CRGB(0,0,0);
  }  
  FastLED.show();
}
