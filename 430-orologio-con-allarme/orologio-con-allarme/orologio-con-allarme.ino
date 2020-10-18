//RTCLib by Adafruit x DS1307
#include "RTClib.h"

#include <U8x8lib.h>
U8X8_SSD1306_128X64_ALT0_HW_I2C oled(U8X8_PIN_NONE); 

RTC_DS1307 rtc;
DateTime now;

int alarmh, alarmm, alarms;
bool ALARM = false;
char str[3];
int stato = 0;

void setup () {
  Serial.begin(9600);

  //pulsanti set e reset
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, OUTPUT);
  
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(500);
  digitalWrite(3, HIGH);
  oled.begin();
  oled.setFont(u8x8_font_5x7_f);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}

void loop () {
  switch(stato){
    case 0:
      displayTime();
      break;  
    case 1:
      setHour();
      break;
    case 2:
      setMinute();
      break;
    case 3:
      setSecond();
      break;
    case 20:
      setAlarm();
      break;
    case 21:
      setAHour();
      break;
    case 22:
      setAMinute();
      break;
    case 23:
      setASecond();
      break;
    case 30:
      ringing();
      break;
  }   
}

unsigned long t1, dt;
bool FIRST = true;

int ch, cm, cs;

void displayTime() {
  if (FIRST) {
    oled.clear();
    t1 = millis();
    FIRST = false;
  }        
  
  dt = millis() - t1;
  if (dt > 500) {
    now = rtc.now();    
    oled.setCursor(0,0);  
    ch = now.hour();
    cm = now.minute();
    cs = now.second();
    
    sprintf(str, "%02d", ch);
    oled.print(str);
    oled.print(':');
    sprintf(str, "%02d", cm);
    oled.print(str);
    oled.print(':');
    sprintf(str, "%02d", cs);
    oled.print(str); 

    oled.setCursor(0,1);
    if (ALARM){      
      oled.print("SVEGLIA ON"); 
    } else {
      oled.print("          ");   
    }
    t1 = millis();   

    if ((ch == alarmh) && (cm == alarmm) && (cs == alarms)) {
      stato = 30;
      FIRST = true;
    }
  }

  if (digitalRead(4)) {
    //imposta ora
    stato = 1;  
    delay(300);
    FIRST = true;
  }
  if (digitalRead(5)) {
    //imposta l'allarme
    stato = 20;  
    delay(300);
    FIRST = true;
  }
}

int seth = 0;

void setHour() {
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    seth = now.hour();
    oled.setCursor(0,0);
    oled.print("Imposta ora");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", seth);
  oled.print(str);

  if (digitalRead(5)) {
    seth++;
    if (seth >= 24) seth = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva ora scelta e passa ai minuti
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), seth, now.minute(), now.second()));
    stato = 2;
    FIRST = true;
    delay(200);
  }
}

int setm;
void setMinute(){
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    setm = now.minute();
    oled.setCursor(0,0);
    oled.print("Imposta minuti");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", setm);
  oled.print(str);

  if (digitalRead(5)) {
    setm++;
    if (setm >= 60) setm = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva min scelta e passa ai sec
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), setm, now.second()));
    stato = 3;
    delay(200);
    FIRST = true;
  }  
}

int sets = 0;

void setSecond(){
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    sets = now.second();
    oled.setCursor(0,0);
    oled.print("Imposta sec.");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", sets);
  oled.print(str);

  if (digitalRead(5)) {
    sets++;
    if (sets >= 60) sets = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva sec scelta e passa ai minuti
    rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), now.minute(), sets));
    stato = 0;
    delay(200);
    FIRST = true;
  }  
}

void setAlarm(){
  if (FIRST) {
    oled.clear();
    oled.setCursor(0,0);
    oled.print("Imposta Sveglia");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  if (ALARM) {
    oled.print("ATTIVA    ");
  } else {
    oled.print("NON ATTIVA");
  }
 
  if (digitalRead(5)) {
    ALARM = !ALARM;    
    delay(200);  
  }
  if (digitalRead(4)) {
    if (!ALARM) stato = 0;
    else stato = 21;
    delay(200);
    FIRST = true;
  }  
}

void setAHour() {
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    alarmh = now.hour();
    oled.setCursor(0,0);
    oled.print("Set ora sveglia");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", alarmh);
  oled.print(str);

  if (digitalRead(5)) {
    alarmh++;
    if (alarmh >= 24) alarmh = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva ora scelta e passa ai minuti
    stato = 22;
    FIRST = true;
    delay(200);
  }
}

void setAMinute() {
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    alarmm = now.minute();
    oled.setCursor(0,0);
    oled.print("Set min sveglia");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", alarmm);
  oled.print(str);

  if (digitalRead(5)) {
    alarmm++;
    if (alarmm >= 60) alarmm = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva min scelta e passa ai minuti
    stato = 23;
    FIRST = true;
    delay(200);
  }
}

void setASecond() {
  if (FIRST) {
    oled.clear();
    now = rtc.now();
    alarms = now.second();
    oled.setCursor(0,0);
    oled.print("Set sec sveglia");      
    FIRST = false;
  }        
  oled.setCursor(0,1);      
  sprintf(str, "%02d", alarms);
  oled.print(str);

  if (digitalRead(5)) {
    alarms++;
    if (alarms >= 60) alarms = 0;
    delay(200);  
  }
  if (digitalRead(4)) {
    //salva sec 
    stato = 0;
    FIRST = true;
    delay(200);
  }
}

int ringing(){
  if (FIRST) {
    oled.clear();
    oled.setCursor(0,0);
    oled.print("SVEGLIA!!");
    FIRST = false;
  }
  tone(6, 440, 100);
  delay(100);
  if (digitalRead(4) || digitalRead(5)) {
    FIRST = true;
    stato = 0;
    delay(300);  
  }
}
