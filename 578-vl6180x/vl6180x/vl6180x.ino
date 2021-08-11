#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VL6180X.h"

Adafruit_VL6180X vl = Adafruit_VL6180X();

Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.clearDisplay();
  
  if (!vl.begin()) {
    Serial.println("Failed to find sensor");
    while (1);
  }
}

char str[10];

void loop() {
  float lux = vl.readLux(VL6180X_ALS_GAIN_5);
  int range = vl.readRange();
  uint8_t status = vl.readRangeStatus();
  if (status == VL6180X_ERROR_NONE) {
    Serial.print(lux);
    Serial.print(" ");
    Serial.println(range);
    display.clearDisplay();
    display.setCursor(0,0);
    dtostrf(lux, 5,4, str);
    display.write("Lux: ");
    display.write(str);
    display.setCursor(0,16);
    display.write("D: ");
    sprintf(str, "%d", range);
    display.write(str);
    display.display();
  }
  delay(200);
}
