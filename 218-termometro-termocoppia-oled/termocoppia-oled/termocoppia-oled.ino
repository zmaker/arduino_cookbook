#include <MAX6675_Thermocouple.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define SCK_PIN 10
#define CS_PIN  9
#define SO_PIN  8
MAX6675_Thermocouple thermocouple = MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);

void setup() {  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("Error..."));
    for(;;);
  }    
  display.display();  
  display.clearDisplay(); 
}


void loop() {
  double celsius = thermocouple.readCelsius();
  //double kelvin = thermocouple->readKelvin();
  //double fahrenheit = thermocouple->readFahrenheit();
  
  display.clearDisplay();  
  display.setTextSize(2);      
  display.setTextColor(WHITE); 
  display.setCursor(0, 0);
  display.print(celsius);  
  display.print(" C");
  display.display();
  delay(500);
}

