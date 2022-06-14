#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include <ArduinoJson.h> 

#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h" 
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

int status = WL_IDLE_STATUS;

char server[] = "api.openweathermap.org";    // name address for Google (using DNS)
char page[] = "/data/2.5/forecast?q=Lodi,IT&cnt=1&appid=";
String appid = "000000000000000000000000000";

WiFiClient client;

void setup() {  
  Serial.begin(9600);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text  
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.clearDisplay();

  display.setCursor(0, 0);
  display.println("Meteo Station");
  display.display();
  
  if (WiFi.status() == WL_NO_MODULE) {
    //Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, pass);
    if (status != WL_CONNECTED) delay(5000);
  }
  Serial.println("call");
  if (client.connect(server, 80)) {
    String url = String(page) + appid;
    client.println("GET "+url+" HTTP/1.1");
    client.println("Host: "+String(server));
    client.println("Connection: close");
    client.println();
  }
  //_____________
  
  String line = "";
  String json;
  int byte_to_read;
  DynamicJsonDocument doc(1500);
  while(true) {
    while (client.available()) {
      char c = client.read();
      //Serial.write(c);  
      if (c == '\n') {
        
        if (line.indexOf("Content-Length: ") >= 0) {
          String str = line.substring(line.indexOf(":")+1);
          byte_to_read = str.toInt();              
          Serial.print("byte to read: ");Serial.println(byte_to_read);             
        }
        if (line.length() == 0) {
          DeserializationError error = deserializeJson(doc, client);
          if (error) {
            Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.f_str());
            client.stop();
            return;
          }
          String meteo = doc["list"][0]["weather"][0]["main"].as<const char*>(); 
          float temp = doc["list"][0]["main"]["temp"].as<float>() - 273.15; 
          float humi = doc["list"][0]["main"]["humidity"].as<float>();
           
          // Print values. 
          Serial.println(meteo); 
          Serial.println(temp); 
          Serial.println(humi); 
        
          display.setCursor(0, 10);
          display.println(meteo);
          display.setCursor(0, 20);
          display.print(temp); display.print("C ");
          display.print(humi); display.print("%");
          display.display();
        
          break;
        }
        
        line = "";
      } else if (c != '\r') {
        line += c;  
      }
    }

    if (!client.connected()) {
      Serial.println("\n\nScollegato dal server web");
      client.stop();
      break;
    }
  }
  Serial.println("disconnect wifi");
  WiFi.disconnect();
  Serial.println("shutdown modulo");
  WiFi.end();
}

void loop() {
  
}
