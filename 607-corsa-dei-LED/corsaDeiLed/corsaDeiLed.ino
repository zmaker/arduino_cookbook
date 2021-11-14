/**
 * Sketch base - gestisce il movimento di 1 led sulla striscia ad anello con velocità decrescente
 */
#include <FastLED.h>
#define NUM_LEDS 50

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  
  FastLED.addLeds<WS2812, 5, BRG>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

int xa = 0;
int vela = 0;
int prevb1, b1;

unsigned long t1;

void loop() {
  int b1 = digitalRead(2);
  if (b1 && !prevb1) {
    //FDS
    vela = 3;    
    Serial.println("fds");
  }

  if ((millis() -t1) > 100) {
    leds[xa] = CRGB::Black; 
    xa += (vela > 0 ? 1 : 0);
    //accendo i led
    leds[xa] = CRGB::Blue;

    if (vela > 0) {
    vela--;
    
    } else if (vela < 0) {
      vela = 0;
    }
    
    if (xa >= NUM_LEDS) {
      xa = 0;
    }
    FastLED.show(); 
    t1 = millis();
  }
  
  prevb1 = b1; 
}
