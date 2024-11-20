// RTCLib - Neiro
#include <RTClib.h>
DS3231 rtc;

int bt1, bt2, pv_bt1, pv_bt2;
int stato = 0;
unsigned long t1, t2;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
}

void loop() {
  if ((millis() - t1) > 500) {
    t1 = millis();
    DateTime now = rtc.now();
    int hh = now.hour();
    int mi = now.minute();

    Serial.print(hh);
    Serial.print(":");
    Serial.println(mi);
  }

  bt1 = !digitalRead(2);
  bt2 = !digitalRead(3);

  switch (stato) {
    case 0:
    runclock();
    break;
    case 1:
    sethours();
    break;
    case 2:
    setminutes();
    break;
  }

  pv_bt1 = bt1;
  pv_bt2 = bt2;
}

void runclock(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt1...");
  } 
  if (!bt1 && pv_bt1) { //FDD
    if ((millis() - t2) > 2000) {
      Serial.println("set->sethour");
      stato = 1;
    }
  }
}
void sethours(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt1->setmin");
    delay(300);
    stato = 2;
  } 
  if (bt2 && !pv_bt2) { //FDS
    Serial.println("h+");
    DateTime now = rtc.now();
    int hh = now.hour() + 1;
    if (hh >= 24) hh = 0;
    DateTime dt0(now.year(), now.month(), now.day(), hh, now.minute(), now.second());
    rtc.adjust(dt0);
  } 
}
void setminutes(){
  if (bt1 && !pv_bt1) { //FDS
    t2 = millis();
    Serial.println("bt2->setmin");
    delay(300);
    stato = 0;
  } 
  if (bt2 && !pv_bt2) { //FDS
    Serial.println("m+");
    DateTime now = rtc.now();
    int mi = now.minute() + 1;
    if (mi >= 60) mi = 0;
    DateTime dt0(now.year(), now.month(), now.day(), now.hour(), mi, now.second());
    rtc.adjust(dt0);
  }
}
