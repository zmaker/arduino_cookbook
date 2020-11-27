#include <FastLED.h>

CRGB leds[8];

void setup() {
  Serial.begin(9600);  
  clearleds();
  randomSeed(analogRead(A0));
}

int i,t = 0;
int r,b,g;

void loop() {
  t = random(5, 30);
  r = random(0, analogRead(A5));
  g = random(0, analogRead(A4));
  b = random(0, 32);
  leds[i] = CRGB(r, g, b);
  i++;  
  if (i > 8) i = 0;
  FastLED.show();
  delay(t);    
}

void clearleds() {
  FastLED.addLeds<WS2812, 2, GRB>(leds, 8);
  for (int i = 0; i < 8; i++) {
    leds[i] = CRGB(0,0,0);
  }  
  FastLED.show();
}
