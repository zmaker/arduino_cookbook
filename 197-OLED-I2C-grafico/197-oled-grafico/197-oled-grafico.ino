#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  // Clear the buffer
  display.clearDisplay();  
  
}

void loop() {
  
  for (int x = 0; x < 128; x++) {
    display.clearDisplay();    
    display.drawPixel(x, 10, WHITE);
    display.display();
  }
  delay(1000);
  for (int y = 0; y < 32; y++) {
    display.clearDisplay();
    display.drawLine(0, y, 128, y, WHITE);
    display.display();
  }
  for (int y = 32; y >= 0; y--) {
    display.clearDisplay();
    display.drawLine(0, y, 128, y, WHITE);
    display.display();
  }
  delay(1000);
}
