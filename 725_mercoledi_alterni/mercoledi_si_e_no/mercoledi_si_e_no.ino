#include "RTClib.h"
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }


  DateTime now = rtc.now();

  int yy = now.year();
  int mm = now.month();
  int dd = now.day();

  dd = 11;
  mm = 1;
  yy = 2023;

  unsigned long di = yy*365 + getGiorniDaInizioAnno(mm, yy) + dd;

  Serial.print("di=");Serial.println(di);
  Serial.print("resto=");Serial.println((di%14));

  if ((di%14) == 3) {
    Serial.println("merc1");
  } else if ((di%14) == 10) { 
    Serial.println("merc2");
  }
}

void loop() {}

int getGiorniDaInizioAnno(int mese, int anno){
  int n = 0;
  for (int i = 1; i < mese; i++) {
      n += getGiorniMese(mese, anno);
  }
  return n;
}

int getGiorniMese(int mese, int anno){
  if (mese == 2){
    if ((anno % 4) == 0 ) {
      return 29;
    } else {
      return 28;
    }
  } else if ((mese == 4) || (mese == 6) || (mese == 9) || (mese == 11)){
     return 30;
  }
  return 31; 
}
