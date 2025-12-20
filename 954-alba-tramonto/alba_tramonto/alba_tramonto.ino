#include "RTClib.h"
unsigned long t1, pvt1;

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);

  if (!rtc.begin()) {
    Serial.println("RTC ko - verifica connessioni");
    while(true);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  t1 = getTimeCounter();
  pvt1 = t1;

  //setup
  for (unsigned long t = 0; t < t1; t++) {
    if (t == timeToSeconds(7, 15)) {
      digitalWrite(10, HIGH);
    } else if (t == timeToSeconds(18, 5)) {
      digitalWrite(10, LOW);
    }  
  }
}

void loop() {
  t1 = getTimeCounter();

  if (t1 != pvt1) {
    Serial.println(t1);
    if (t1 == timeToSeconds(7, 15)) {
      digitalWrite(10, HIGH);
    } else if (t1 == timeToSeconds(18, 5)) {
      digitalWrite(10, LOW);
    } 
  }

  pvt1 = t1;
}

unsigned long getTimeCounter(){
  DateTime now = rtc.now();
  unsigned long t = now.second() + now.minute()*60 + now.hour() * 3600;
  return t;
}

unsigned long timeToSeconds(int hh, int mm){
  unsigned long t = mm*60 + hh * 3600;
  return t;
}
