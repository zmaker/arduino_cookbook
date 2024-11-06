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
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() {
  for (int i = 0; i < 180; i++) {
    display.clearDisplay();
    // ar : 6.28 = as : 360
    float a = ((float)i*3.14f) / 180.0;
    meter(a);
    display.display();
    delay(10);
  }
}

void meter(float a){
  const float r = SCREEN_WIDTH / 2;

  for (int i = 0; i < 180; i += 10){
    float a = ((float)i*3.14f) / 180.0;
    int xp = SCREEN_WIDTH/2 - r*cos(a);
    int yp = SCREEN_HEIGHT - r*sin(a);    
    display.drawPixel(xp, yp, SSD1306_WHITE);  
  }

  int x = SCREEN_WIDTH/2 - r*cos(a);
  int y = SCREEN_HEIGHT - r*sin(a);
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT, x, y, SSD1306_WHITE);
}



