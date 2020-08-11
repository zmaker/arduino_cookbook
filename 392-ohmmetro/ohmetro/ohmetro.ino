#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  display.clearDisplay();    
}

float rx, v1 = 0;
float r1 = 1000; //1kohm resistenza nota

void loop() {
  int n = analogRead(A0); 
  
  v1 = map(n, 0, 1024, 0, 5000)/1000.0; //mV
  rx = (r1*(5.0-v1)) / v1;
  
  /*
  Serial.print(n);
  Serial.print("\t");
  Serial.print(v1);
  Serial.print("\t");
  Serial.println(rx);
  */
  
  display.clearDisplay();  
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  if (rx > 1000) {
    rx = rx / 1000.0;
    display.print(rx);
    display.print("K");
  } else {
    display.print(rx);
    display.print("R");
  }
  display.display();
  delay(200);
  
}
