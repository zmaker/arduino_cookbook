#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

/**
 * La libreria LEDControl è reperibile qui:
 * http://wayoda.github.io/LedControl/
 * Oppure nel library manager come: LedControl di Eberhard Fahle
 */
#include "LedControl.h"

#define pinCLK 4
#define pinCS 3
#define pinDIN 2

#define ELEMENTS 8
LedControl lc = LedControl(pinDIN, pinCLK, pinCS, ELEMENTS);  

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < ELEMENTS ; i++) {
    lc.shutdown(i,false);  // Wake up displays  
    lc.setIntensity(i,1);  // 0-15
    lc.clearDisplay(i);  // Clear Displays
  }
  Serial.println("ok");

  if (!rtc.begin()) {
    Serial.println("Controlla le connessioni");
    while(true);
  }

  if (rtc.lostPower()) {
    Serial.println("Imposto data/ora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
}

void loop() {  
  DateTime now = rtc.now();

  bool led = false;
  int h = now.hour();
  for (int i = 0; i < 8; i++) {
     led = false;
     if (h & (1 << i)) {
       led = true;
     }
     pixel(0, 7-i,led);
  }

  int m = now.minute();
  for (int i = 0; i < 8; i++) {
     led = false;
     if (m & (1 << i)) {
       led = true;
     }
     pixel(1, 7-i,led);
  }
  
  int s = now.second();
  for (int i = 0; i < 8; i++) {
     led = false;
     if (s & (1 << i)) {
       led = true;
     }
     pixel(2, 7-i,led);
  }
  
/*  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(pad(now.month()));
  Serial.print('/');
  Serial.print(pad(now.day()));
  Serial.print(" - ");
  Serial.print(pad(now.hour()));
  Serial.print(':');
  Serial.print(pad(now.minute()));
  Serial.print(':');
  Serial.print(pad(now.second()));
  Serial.println();
  */
 /*
  //estraggo i caratteri di messaggio e li stampo    
  for (int i = 0; i < sizeof(orario); i++) {
    char c = orario[i];
    //ricavo l'array da visualizzare
    //la sua posizione 
    int id = findInMap(c);
    //visualizzo lo sprite con la lettera
    int xlettera = i*8;
    drawSprite(xlettera,1, alpha[id]);
  } 
*/
  delay(500);
}

void pixel(int x, int y, bool stato){  
  int el = (int)(x / 8);
  int xloc = 7-(x - (8*el));
  y = 7 - y;
  lc.setLed(el,y,xloc, stato);
}
