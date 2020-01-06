#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

MCUFRIEND_kbv tft;

void setup() {
  int id = tft.readID();
  tft.begin(id);

  tft.setRotation(1); 
  tft.setTextSize(2);
  tft.setTextColor(0xFFFF, 0x0000);
}

int n = 0;

void loop() {
  tft.fillScreen(0x0000);
  tft.setCursor(0,0);
  tft.println("hello World!");
  tft.println(n);
  n++;
  delay(1000);
}
