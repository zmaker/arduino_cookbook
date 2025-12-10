#include "RTClib.h"

RTC_DS3231 rtc;
unsigned long tc, pvtc;

void setup () {
  Serial.begin(9600);

  pinMode(10, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  tc = getTimeCounter();
  pvtc = tc;
  
}

void loop () {
  tc = getTimeCounter();
  //Serial.println(tc);

  if (tc != pvtc) {
    Serial.println(tc);
    if (tc == timeToSeconds(7, 15)) {
      digitalWrite(10, HIGH);
    } else if (tc == timeToSeconds(18, 7)) {
      digitalWrite(10, LOW);
    }
  }

  pvtc = tc;
}

unsigned long getTimeCounter(){
  /*
  static unsigned long t0 = timeToSeconds(18, 6);
  unsigned long t = t0++;
  delay(200);
  */
  DateTime now = rtc.now();
  unsigned long t = now.second() + now.minute()*60 + now.hour() * 3600;
  return t;
}

unsigned long timeToSeconds(int hh, int mm){
  unsigned long t = mm*60 + hh * 3600;
  return t;
}