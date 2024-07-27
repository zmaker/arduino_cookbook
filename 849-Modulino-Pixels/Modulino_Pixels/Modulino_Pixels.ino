#include <Modulino.h>

ModulinoPixels pix;

ModulinoColor BLACK(0,0,0);
ModulinoColor YELL(255,230,50);
ModulinoColor MyCOL(120,200,130);

void setup() {
  Modulino.begin();
  pix.begin();

  int lum = 25; // 0 - 255
  pix.set(0, BLUE, lum);
  pix.set(1, RED, lum);
  pix.set(2, GREEN, lum);
  pix.set(3, VIOLET, lum);
  pix.set(4, WHITE, lum);
  pix.set(5, BLACK, lum);
  pix.set(6, YELL, lum);
  pix.set(7, MyCOL, lum);
  pix.show();

  delay(1000);
  pix.clear();
  delay(1000);

  for (int i = 0; i < 10; i++){
    pix.set(0, BLUE, 0);
    pix.show();
    delay(300);
    pix.set(0, BLUE, 255);
    pix.show();
    delay(300);
  }
}

void loop() {
  for (int i = 0; i < 256; i++){
    pix.set(0, BLUE, i);
    pix.show();
    delay(10);
  }
}
