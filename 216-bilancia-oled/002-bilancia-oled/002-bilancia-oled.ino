#include "HX711.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

HX711 scale(2, 3);

float calibration_factor = -1944; 
float units;

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Error..."));
    for(;;);
  }  
  // the library initializes this with an Adafruit splash screen.
  display.display();  
  display.clearDisplay();  

  scale.set_scale();
  scale.tare(); 
  scale.set_scale(calibration_factor); 
}



void loop() {
  units = scale.get_units(); 
  if (units < 0) {
    units = 0.00;
  }
  
  display.clearDisplay();  
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(0, 0);
  display.print(units);
  //display.setCursor(100, 0);
  display.print(" g.");
  display.display();
  delay(200);
  
}
