#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 3D o 3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() {
  for (int h = 0; h < 12; h++){
    for (int m = 0; m < 60; m++){
      display.clearDisplay();
      clock(h, m);
      display.display();
      delay(100);
    }
  }
}

void clock(int hh, int mm) {
  const float r = (SCREEN_HEIGHT/2) - 5;
  const float rh = (SCREEN_HEIGHT/2) * 0.5;
  const float rm = (SCREEN_HEIGHT/2) * 0.8;

  float a = 0;
  //ore
  a = (6.28/12.0) * (float)hh;
  int xh = SCREEN_WIDTH/2 + rh*sin(a);
  int yh = SCREEN_HEIGHT/2 - rh*cos(a);
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xh, yh, SSD1306_WHITE);
  //min
  a = (6.28/60.0) * (float)mm;
  int xm = SCREEN_WIDTH/2 + rm*sin(a);
  int ym = SCREEN_HEIGHT/2 - rm*cos(a);
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, xm, ym, SSD1306_WHITE);
  //corona
  for (int i = 0; i < 360; i = i + 15) {
    a = ((float)i * 3.14) / 180.0;
    int xp = SCREEN_WIDTH/2 + r*sin(a);
    int yp = SCREEN_HEIGHT/2 - r*cos(a);
    if (i%30) {
      display.drawPixel(xp, yp, SSD1306_WHITE);
    } else {
      display.fillCircle(xp, yp, 1, SSD1306_WHITE);
    }
  }
} 


