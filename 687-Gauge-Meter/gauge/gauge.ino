#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET     2 
#define SCREEN_ADDRESS 0x3C 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int xc, yc, xp, yp;
char str[10];
unsigned long t1;

void setup() {
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  
  display.clearDisplay();
  xc = display.width()/2;
  yc = display.height()/2;
}

void loop() {
  if ((millis() - t1) > 100) {
    display.clearDisplay();
    int v = analogRead(A0);
    int perc = map(v, 0, 1023, 0, 100);
    v = map(v, 0, 1023, 0, 628);
    float a = ((float)v)/100.0 - (PI/2.0);
    
    display.setCursor(2, 2);  
    sprintf(str,"%d %%", perc);
    display.write(str);    
  
    xp = xc + (int)(cos(a) * 30.0);
    yp = yc + (int)(sin(a) * 30.0);
    Serial.print(perc);
    Serial.print("\ta:");
    Serial.print(a);
    Serial.print("\tx:");
    Serial.print(xp);
    Serial.print("\ty:");
    Serial.println(yp);
  
    display.drawCircle(xc, yc, 30, SSD1306_WHITE);
    display.drawLine(xc,yc, xp, yp, SSD1306_WHITE);
    display.display();  
    t1 = millis();
  }
  
}
