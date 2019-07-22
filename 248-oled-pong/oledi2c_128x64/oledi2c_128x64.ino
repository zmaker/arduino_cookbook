#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

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

int x = 50;
int y = 50;
int incx = 1;
int incy = 1;

void loop() {
  display.clearDisplay(); 

  //display.fillRect(i, i, display.width()-i*2, display.height()-i*2, INVERSE);
  display.fillRect(x, y, 5, 5, INVERSE);
   
  display.display();
  delay(10);
  x = x + incx;
  if ((x > display.width() - 5) || (x < 0)) {
    incx = -incx;
  }
  y = y + incy;
  if ((y > display.height() - 5) || (y < 0)) {
    incy = -incy;
  }
}
