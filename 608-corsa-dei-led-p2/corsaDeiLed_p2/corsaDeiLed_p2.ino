#include <FastLED.h>
#define NUM_LEDS 50

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  
  FastLED.addLeds<WS2812, 5, BRG>(leds, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}

int xa = 0;
int vela = 0;
int prevb1, b1;

int xb = 0;
int velb = 0;
int prevb2, b2;

unsigned long t1;

void loop() {
  b1 = digitalRead(2);
  if (b1 && !prevb1) {
    //FDS
    vela = 3;        
  }
  b2 = digitalRead(3);
  if (b2 && !prevb2) {
    //FDS
    velb = 3;        
  }

  if ((millis() - t1) > 100) {
    leds[xa] = CRGB::Black; 
    leds[xb] = CRGB::Black; 
    xa += (vela > 0 ? 1 : 0);
    //accendo i led
    leds[xa].setRGB(0,0,255);

    if (vela > 0) {
    vela--;
    
    } else if (vela < 0) {
      vela = 0;
    }
    
    if (xa >= NUM_LEDS) {
      xa = 0;
    }
    //
    
    xb += (velb > 0 ? 1 : 0);
    //accendo i led
    leds[xb].setRGB(255,0,0);

    if (xa == xb) leds[xb].setRGB(255,0,255);

    if (velb > 0) {
      velb--;    
    } else if (velb < 0) {
      velb = 0;
    }
    
    if (xb >= NUM_LEDS) {
      xb = 0;
    }
    FastLED.show(); 
    t1 = millis();
  }
  
  prevb1 = b1; 
}
