#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define EL 16
#define PIN 6

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(EL, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();

  for (int i = 0; i < EL; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));  
  }
  pixels.show();
  delay(1000);
}

int c = 0;

void loop() {
  for (int i = 0; i < EL; i++) {
    int r = (c % EL);
    if (i == r) {
      pixels.setPixelColor(i, pixels.Color(0,120,120));  
    } else {
      pixels.setPixelColor(i, pixels.Color(0,0,0));    
    }    
  }
  pixels.show();
  delay(1000);
  c++;
}


