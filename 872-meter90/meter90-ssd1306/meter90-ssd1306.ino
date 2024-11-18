#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C // 3D o 3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  //Serial.begin(115200);
  //while(!Serial);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  for (int i = 0; i < 90; i++) {
    /*
    ar : 6.28 = as : 360
    ar = (6.28 * as) / 360 = (3.14*as) / 180
    */
    float a = ((float)i * 3.14f) / 180.0f;
    display.clearDisplay();
    meter(a);
    display.display();
    delay(10);
  }
}

void meter(float a) {
  const float r = SCREEN_WIDTH / 2;

  //corona
  for (int i = 0; i < 90; i += 10) {
    float a = ((float)i * 3.14f) / 180.0f;
    int xp = (int)(r * sin(a) + SCREEN_WIDTH / 2);
    int yp = (int)(SCREEN_HEIGHT - r * cos(a));  
    display.drawPixel(xp,yp, SSD1306_WHITE);
  }

  int x = (int)(r * sin(a) + SCREEN_WIDTH / 2);
  int y = (int)(SCREEN_HEIGHT - r * cos(a));
  display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT, x,y, SSD1306_WHITE);
}



