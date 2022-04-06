//libreria grove
#include "TM1637.h"

#include <SPI.h>
#include <WiFiNINA.h>
#include <NTPClient.h>

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)
int status = WL_IDLE_STATUS;
//WiFiClient client;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

//pins definitions for TM1637 and can be changed to other ports
#define CLK 2
#define DIO 3
TM1637 tm1637(CLK,DIO);

int fuso = 2;

unsigned long t1;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");    
    while (true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);    
    delay(5000);
  }
  Serial.println("Connected to WiFi");

  timeClient.begin();
  
  tm1637.init();
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.set(BRIGHT_TYPICAL);
  //tm1637.point(POINT_ON);

  tm1637.display(0,1);
  tm1637.display(1,2);
  tm1637.display(2,3);
  tm1637.display(3,4);

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
    Serial.print(hh); Serial.print(":"); Serial.println(mm); 
    //la spacchetto in 4 digit
    int d1 = hh % 10;
    int d2 = (hh/10) % 10;
    int d3 = mm % 10;
    int d4 = (mm/10) % 10;
    tm1637.display(0,d2);
    tm1637.display(1,d1);
    tm1637.display(2,d4);
    tm1637.display(3,d3);
    
    t1 = millis();  
  }
}
