#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

void setup() {
  pinMode(13, OUTPUT);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    digitalWrite(13, HIGH);
    for(;;);
  }
  display.display();
  display.clearDisplay();    
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  int v = analogRead(A0);
  display.clearDisplay();  
  display.setCursor(0, 0);
  display.print("V=");
  display.print(v);
  display.display();
  delay(100);
}
