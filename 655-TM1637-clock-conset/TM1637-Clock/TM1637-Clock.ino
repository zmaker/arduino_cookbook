#include <Wire.h>
#include "RTClib.h"
//libreria grove
#include "TM1637.h"

RTC_DS3231 rtc;

#define CLK 2//pins definitions for TM1637 and can be changed to other ports
#define DIO 3
TM1637 tm1637(CLK,DIO);

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("Controlla le connessioni");
    while(true);
  }

  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
  if (rtc.lostPower()) {
    Serial.println("Imposto data/ora");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));    
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  tm1637.init();
  //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  tm1637.set(BRIGHT_TYPICAL);
  //tm1637.point(POINT_ON);
}

unsigned long t1;

void loop() {
  static bool fpoint;
  
  if ((millis() - t1) > 500) {    
    fpoint = !fpoint;
    //Serial.println(fpoint);
    tm1637.point(fpoint);

    //ricavo l'ora corrente
    DateTime now = rtc.now();
    int hh = now.hour();
    int mm = now.minute();
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
