#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    50

CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
}

void loop() {
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(50);
  int t = 0;
  for (int i = 1; i < NUM_LEDS; i++) {
    leds[i-1] = CRGB(0, 0, 0);
    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);
    leds[i] = CRGB(r, g, b);
    FastLED.show();
    t = map (i, 0, NUM_LEDS, 50, 1);
    delay(t);
  }
  for (int i = NUM_LEDS; i > 0; i--) {
    leds[i] = CRGB(0, 0, 0);
    int r = random(0, 255);
    int g = random(0, 255);
    int b = random(0, 255);
    leds[i-1] = CRGB(r, g, b);
    FastLED.show();
    t = map (i, 0, NUM_LEDS, 50, 1);
    delay(t);
  }
  
}
