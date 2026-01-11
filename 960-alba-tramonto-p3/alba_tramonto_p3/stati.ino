void go(int st) {
  stato = st;
  FIRST = true;
}

void st_run() {
  if (FIRST) {
    Serial.println("RUN");
    spazzolaPin();
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("ora corrente");
    lcd_timer = millis();
    FIRST = false;
  }

  if (bt1 && !pv_bt1) {
    go(10);
    delay(300);
  }
}

void st_set_hour() {
  if (FIRST) {
    Serial.println("SET H");
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set hh    ");
  }
  if (bt1 && !pv_bt1) {
    go(2);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    Serial.println("bt2");
    DateTime now = rtc.now();
    int h = now.hour() + 1;
    h = constrain(h, 0, 23);
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),
      h, now.minute(), now.second()
      ));
    showTime(true);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    Serial.println("bt3");
    DateTime now = rtc.now();
    int h = now.hour() - 1;
    h = constrain(h, 0, 23);
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),
      h, now.minute(), now.second()
      ));
    showTime(true);
    delay(300);
  }
}

void st_set_minute() {
  if (FIRST) {
    Serial.println("SET M");
    FIRST = false;
    lcd.cls();
    lcd.locate(1, 1);
    lcd.printf("set mm");
  }
  if (bt1 && !pv_bt1) {
    go(10);
    delay(300);
  }
  if (bt2 && !pv_bt2) {
    Serial.println("bt2");
    DateTime now = rtc.now();
    int m = now.minute() + 1;
    m = constrain(m, 0, 59);
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),
      now.hour(), m, now.second()
      ));
    showTime(true);
    delay(300);
  }
  if (bt3 && !pv_bt3) {
    Serial.println("bt3");
    DateTime now = rtc.now();
    int m = now.minute() - 1;
    m = constrain(m, 0, 59);
    rtc.adjust(DateTime(now.year(), now.month(), now.day(),
      now.hour(), m, now.second()
      ));
    showTime(true);
    delay(300);
  }
}

void spazzolaPin(){
  t1 = getTimeCounter();
  digitalWrite(10, LOW);
  for (unsigned long t = 0; t < t1; t++) {
    if (t == timeToSeconds(ALBA_H, ALBA_M)) {
      digitalWrite(10, HIGH);
    } else if (t == timeToSeconds(TRAM_H, TRAM_M)) {
      digitalWrite(10, LOW);
    }  
  }
}

void showTime(bool onserial) {
  int pin = digitalRead(10);
  DateTime now = rtc.now();
  lcd.locate(2, 1);
  lcd.printf("%02d:%02d  out:%d", now.hour(), now.minute(), pin);
  if (onserial) {
    char buff[30];
    sprintf(buff, "%04d/%02d/%02d - %02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute());
    Serial.println(buff);
  }

  unsigned long t = now.second() + now.minute()*60 + now.hour() * 3600;
  return t;
}