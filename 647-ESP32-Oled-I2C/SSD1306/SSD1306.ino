/**
 * ESP con SSD1306 
 * Usare lel libreria adafruit + GFX
 * 
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <WiFi.h>
const char* ssid = "www.reelco.it";
const char* password = "cardu450IX";


void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  display.println("Hello world!");
  display.display();
  delay(2000);

  WiFi.mode(WIFI_STA);  //station mode: the ESP32 connects to an access point
  //vedi https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/
  WiFi.begin(ssid, password);

  display.clearDisplay();  
  // Wait for connection
  int x = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.setCursor(x,10);
    display.println("X");
    x += 10;
    display.display();
    Serial.print(".");
  }
  Serial.println("");
  delay(1000);

  display.clearDisplay();  
  display.setCursor(0,10);
  display.println(WiFi.localIP());
  display.display();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
