// lib lcd di Stefan Staub
// LCD-I2c-HD44780
#include <LCDi2c.h>
LCDi2c lcd(0x27, Wire);
//timer display
unsigned long lcd_timer;

//pulsanti
int bt1, bt2, bt3, pv_bt1, pv_bt2, pv_bt3;
int stato = 0;
bool FIRST = true;

#include "RTClib.h"
unsigned long t1, pvt1;

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);

  pinMode(10, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  lcd.begin(2, 16);
  lcd.display(DISPLAY_ON);
  lcd.display(BACKLIGHT_ON);
  lcd.cls();
  lcd.printf("alba tramonto");

  if (!rtc.begin()) {
    Serial.println("RTC ko - verifica connessioni");
    lcd.locate(2,1);
    lcd.printf("RTC error");
    while(true);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  t1 = getTimeCounter();
  pvt1 = t1;

  //setup
  spazzolaPin();
}

void loop() {
  t1 = getTimeCounter();

  //lettura pulsanti
  bt1 = !digitalRead(2);
  bt2 = !digitalRead(3);
  bt3 = !digitalRead(4);

  if (t1 != pvt1) {
    //Serial.println(t1);
    if (t1 == timeToSeconds(7, 15)) {
      digitalWrite(10, HIGH);
    } else if (t1 == timeToSeconds(18, 5)) {
      digitalWrite(10, LOW);
    } 
  }

  switch (stato) {
    case 0:
      st_run();
      break;
    case 1:
      st_set_hour();
      break;
    case 2:
      st_set_minute();
      break;
  }

  //aggiorna lcd
  if ((millis() - lcd_timer) > 250) {
    showTime(false);
    lcd_timer = millis();
  }

  pvt1 = t1;
  pv_bt1 = bt1;
  pv_bt2 = bt2;
  pv_bt3 = bt3;
}

unsigned long getTimeCounter(){
  DateTime now = rtc.now();
  unsigned long t = now.second() + now.minute()*60l + now.hour() * 3600l;
  return t;
}

unsigned long timeToSeconds(int hh, int mm){
  unsigned long t = mm*60l + hh * 3600l;
  return t;
}
