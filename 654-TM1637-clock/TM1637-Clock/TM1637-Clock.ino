#include <Wire.h>
#include "RTClib.h"
#include "TM1637.h"

RTC_DS3231 rtc;

#define PIN_CLK 2
#define PIN_DIO 3
TM1637 tm1637(PIN_CLK, PIN_DIO);

unsigned long t1;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("errore RTC");
    while(true);  
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
  }
  tm1637.init();
  tm1637.set(3); //da 0 a 7
}

void loop() {
  static bool fpoint;
  if ((millis() - t1) >= 500) {
    fpoint = !fpoint;
    tm1637.point(fpoint);

    DateTime now = rtc.now();
    int hh = now.hour();
    int mm = now.minute();
    Serial.print(hh); Serial.print(":"); Serial.println(mm); 

    int d1 = hh%10;
    int d2 = (hh/10)%10;
    int d3 = mm%10;
    int d4 = (mm/10)%10;

    tm1637.display(0, d2);
    tm1637.display(1, d1);
    tm1637.display(2, d4);
    tm1637.display(3, d3);
    t1 = millis(); 
  }
}
