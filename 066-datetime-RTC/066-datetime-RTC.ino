#include <Wire.h>

//installare la RTCLib
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  
  if (!rtc.begin()) {
    Serial.println("Errore! Verifica le connesioni!");
    return;
  }

  if (!rtc.isrunning()) {
    Serial.println("Configuro l'ora");
    //Uso l'ora di compilazione dello sketch
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // per farlo a mano...
    // January 21, 2014 at 3am you would call
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

char settimana[7][4] = {"dom", "lun", "mar", "mer", "gio", "ven", "sab"};

void loop() {
  //chiedo l'ora
  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(settimana[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  delay(2000);
}
