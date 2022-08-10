#include "JoyShield.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     A3 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long t1;
int x = SCREEN_WIDTH / 2;
int y = SCREEN_HEIGHT  / 2; 
int sz = 3;

enum directions {none, up, down, left, right} dir;

void setup() {
  Serial.begin(9600);
  
  if(!oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  oled.setTextSize(1);      // Normal 1:1 pixel scale
  oled.setTextColor(SSD1306_WHITE); // Draw white text
  oled.cp437(true);         // Use full 256 char 'Code Page 437' font
}

void loop() { 
  int a = analogRead(AXIS_X);
  int b = analogRead(AXIS_Y);
  if (a > 768) dir = right;
  if (a < 256) dir = left;
  if (b > 768) dir = down;
  if (b < 256) dir = up;
  
  if ((millis() - t1) > 100) {
    oled.clearDisplay();

    drawSnake(dir);
         
    oled.display();  
    t1 = millis();
  }
}

void drawSnake(enum directions dir){
  switch (dir){
    case up:
      y++;
      if (y >= SCREEN_HEIGHT) y = 0;
      break;
    case down:
      y--;
      if (y < 0) y = SCREEN_HEIGHT;
      break;
    case right:
      x++;
      if (x >= SCREEN_WIDTH) x = 0;
      break;
    case left:
      x--;
      if (x < 0) x = SCREEN_WIDTH;
      break;
    case none:
      break; 
  }
  Serial.print(dir);Serial.print("\t");Serial.print(x);
  Serial.print("\t");Serial.print(y);Serial.print("\n");
  oled.fillRect(x, y, sz, sz, SSD1306_WHITE);  
}
