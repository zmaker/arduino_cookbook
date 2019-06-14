#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char *res = malloc(5);

void setup() {
  Serial.begin(9600);

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

String pad(int n) {
  sprintf(res, "%02d", n);
  return String(res);  
}

void loop() {
  DateTime now = rtc.now();
   
  Serial.print(now.year(), DEC);
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

}

