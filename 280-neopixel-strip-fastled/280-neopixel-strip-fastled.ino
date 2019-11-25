#include <FastLED.h>

#define NUM_LEDS 50

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, 5, GRB>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

void loop() {
  for (int i = 1; i < NUM_LEDS; i++) {
     leds[i-1] = CRGB(0,0,0); 
     leds[i] = CRGB(255,0,0); 
/*
    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);
    leds[i-1] = CRGB(r, g, b);

    int t = map (i, 0, NUM_LEDS, 50, 1);
    delay(t);
 * 
 */
     
     FastLED.show();
     delay(50);
  }
  for (int i = NUM_LEDS; i > 0; i--) {
     leds[i] = CRGB(0,0,0); 
     leds[i-1] = CRGB(255,0,0); 
     FastLED.show();
     delay(50);
  }
}
