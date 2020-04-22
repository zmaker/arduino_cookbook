#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();  
  display.display();
}

int buff[128];

void loop() {
  for (int i = 0; i < 128; i++) {
    buff[i] = analogRead(A0);  
  }
  
  display.clearDisplay();
  for (int x = 0; x < 128; x++) {
    int y = 2 + map(buff[x], 0, 1024, 60, 0);
    display.drawPixel(x, y, WHITE);
    //Serial.println(y);
  }
  display.display();
  
  //delay(100);
}
