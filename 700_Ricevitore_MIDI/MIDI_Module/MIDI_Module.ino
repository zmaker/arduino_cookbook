#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET    A3 
#define SCREEN_ADDRESS 0x3C 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(31250);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
  display.display();

}

int bc = 0;
byte buff[10];
char str[20];

void loop() {
  while (Serial.available()){
    byte n = Serial.read();
    buff[bc] = n;
    bc++;
  }
  if (bc >= 3) {
    bc = 0;
    display.clearDisplay();
    display.setCursor(2,2);
    sprintf(str, "%d %d %d", buff[0], buff[1], buff[2]);
    display.print(str);
    display.display();
  }

}
