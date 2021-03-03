#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (8)


//#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(128, 32, &Wire, OLED_RESET);

void setup() {  
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  dac.begin(0x60);  //l'originale è a 0x62!!

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    abort();
  }
  display.display();
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.clearDisplay(); 
}

unsigned long t1, dt;
int vel = 0;
bool RUN = false;

void loop() {  
  if (!digitalRead(2)) {
    RUN = !RUN;    
    delay(300);  
  }
  if (!digitalRead(3)) {
    vel++;
    if (vel > 100) vel = 100;
    delay(100);  
  }
  if (!digitalRead(4)) {
    vel--;
    if (vel < 0) vel = 0;
    delay(100);  
  }
  if (RUN){
    digitalWrite(10, HIGH);
    dac.setVoltage(map(vel, 0,100, 0,4095), false);  
  } else {
    digitalWrite(10, LOW);
  }
  dt = millis() - t1;
  if (dt >= 100){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("V: ");
    display.print(vel);
    display.print("%");
    display.setCursor(0, 17);
    if (RUN) {
      display.print("RUN");
    } else {
      display.print("STOP");
    }
    display.display();
    t1 = millis();
  }
}
