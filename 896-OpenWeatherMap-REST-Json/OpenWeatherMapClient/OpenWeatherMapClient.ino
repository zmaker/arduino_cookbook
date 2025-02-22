#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Arduino_JSON.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "www.zeppelinmaker.it";
const char* password = "****************";

String owkey = "xxxxxxxxxxxxxxxxxxxxxxxxx";
String city = "Milan";
String country = "IT";

String jsonBuffer;

unsigned long t1;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.cp437(true);  
  display.clearDisplay();
  display.display();

  display.setCursor(0,0);
  display.print("Connecting...");
  display.display();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("!");
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Connected!");
  display.display();
  delay(2000);

  t1 = 599000;
}

void loop() {
  if ((millis() - t1) >= 600000l) {
    if (WiFi.status() == WL_CONNECTED) {
      String addr = "http://api.openweathermap.org/data/2.5/weather?q="+city+","+country+"&APPID="+owkey;
      Serial.println(addr);

      jsonBuffer = getRequest(addr.c_str());
      Serial.println(jsonBuffer);
      JSONVar obj = JSON.parse(jsonBuffer);
      if (JSON.typeof(obj) == "undefined") {
        Serial.println("Errore json");        
      } else {
        Serial.print("temp: ");
        Serial.println(obj["main"]["temp"]);
        String str = JSON.stringify(obj["main"]["temp"]);
        float temp = str.toFloat() - 273.15f;
        Serial.print("temp (C): ");
        Serial.println(temp);
        Serial.print("hum: ");
        Serial.println(obj["main"]["humidity"]);
        Serial.print("press: ");
        Serial.println(obj["main"]["pressure"]);
        //aggiorno display
        display.clearDisplay();
        display.setCursor(0,0);
        display.print("t: ");
        display.print(temp);
        display.print(" C");
        display.display();
      }

    } else {
      WiFi.disconnect();
      delay(1000);
      WiFi.reconnect();
    }
    t1 = millis();
  }
}

String getRequest(const char* url) {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, url);  
  int code = http.GET();
  String payload = "{}";
  if (code > 0) {
    Serial.print("HTTP CODE: ");Serial.println(code);               
    payload = http.getString(); 
  } else {
    Serial.print("HTTP ERROR: ");Serial.println(code);
  }
  http.end();
  return payload;
}
