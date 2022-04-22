/*
 * scheda: DOIT ESP32 dev kit
 * AZDelivery - https://amzn.to/3GwypiZ
 * Fare UPLOAD e poi premere il tasto RST sulla scheda
 * 
 * URL per config schede: https://dl.espressif.com/dl/package_esp32_index.json
 * 
 * Blink con led sul pin 2
 * 
 */
#include "arduino_secrets.h" 
#include <NTPClient.h>

#include <WiFi.h>
char ssid[] = SECRET_SSID;        // your network SSID (name)
char password[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

//libreria grove
#include "TM1637.h"

#define CLK 17 //pins definitions for TM1637 and can be changed to other ports
#define DIO 16
TM1637 tm1637(CLK,DIO);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

int fuso = 2;
unsigned long t1;

void setup() { 
  Serial.begin(9600);
  
  int i = 0;
  while (!Serial) {
    delay(100);
    i++;
    if (i >= 10) break;
  }
  
   
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  timeClient.begin();
  
  tm1637.init();
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.set(BRIGHT_TYPICAL);
  //tm1637.point(POINT_ON);
  tm1637.display(0,2);

  t1 = millis();
}
 
void loop() {
  static bool fpoint;
  if ((millis() - t1) > 500) {
    fpoint = !fpoint;
    tm1637.point(fpoint);

    //ricavo l'ora corrente
    timeClient.update();
    //Serial.println(timeClient.getFormattedTime());
    
    int hh = timeClient.getHours();
    hh += fuso;
    if (hh >= 24) hh - 24;
    int mm = timeClient.getMinutes();
    //Serial.print(hh); Serial.print(":"); Serial.println(mm); 
    //la spacchetto in 4 digit
    int d1 = hh % 10;
    int d2 = (hh/10) % 10;
    int d3 = mm % 10;
    int d4 = (mm/10) % 10;
    Serial.print(d2);Serial.print(d1); Serial.print(":"); 
    Serial.print(d4);Serial.println(d3); 
    tm1637.display(0,d2);
    tm1637.display(1,d1);
    tm1637.display(2,d4);
    tm1637.display(3,d3);
    
    t1 = millis();  
  }
}
