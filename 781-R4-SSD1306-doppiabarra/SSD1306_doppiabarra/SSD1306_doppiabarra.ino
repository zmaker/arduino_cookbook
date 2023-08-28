#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long t1;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  if ((millis()-t1) > 100) {
    int v = analogRead(A0);
    v = map(v, 0, 1023, 0, display.width()) - display.width()/2;
    Serial.println(v);

    //clear display
    display.clearDisplay();
    //reticolo
    display.drawRect(0, 0, display.width(), 10, SSD1306_WHITE);
    display.drawLine(display.width()/2, 1, display.width()/2, 10, SSD1306_WHITE);

    int x, w;    
    if (v > 0){
      x = display.width() / 2;    
      w = v;
      Serial.print(v);Serial.print("\t x:");Serial.print(x);Serial.print("\t w:");Serial.println(w);
    } else if (v < 0) {
      x = (display.width() / 2) + v; 
      w = -v;
      Serial.print(v);Serial.print("\t x:");Serial.print(x);Serial.print("\t w:");Serial.println(w);
    }
    display.fillRect(x, 0, w, 10, SSD1306_WHITE);
    //display.fillRect(0, 15, 10, 5, SSD1306_WHITE);
    display.display();
    t1 = millis();
  }
}

