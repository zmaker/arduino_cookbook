//#define SIMULA
#define RTC

/**
 * Collegare al pin 2 il relè per i minuti
 * Al pin 3 il relè per i rintocchi delle ore
 * al pin 4 e 5 collegare due pulsanti con resistenza pull down per cambio ora e minuti
 * Rintocchi abilitati dalle 7 alle 19
 * tempo rintocco: 2s
 * Collegare RTC DS3231 via I2c 
 * Collegare display LCD AZDelivery 16x2 con I2C
 * 
 * Installare la libreria 
 * //https://bitbucket.org/fmalpartida/new-liquidcrystal 
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define I2C_ADDR 0x27 
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7

LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

char orario[] = "00:00:00";
int mi, pvmi;
int ho, pvho;
unsigned long t1, t2, currtm;
int sequenza;
int stato_minuti = LOW;
int stato_ora = LOW;

#ifdef SIMULA
unsigned long t3;  //siumulazione
int hh, mm;
#endif

//pulsanti cambio ora
DateTime now;
byte btm, pbtm;
byte bth, pbth;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.home();    
  
  if (!rtc.begin()) {
    Serial.println("Controlla le connessioni");
    while(true);
  }
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  #ifdef SIMULA
  Serial.println("simulazione");
  hh = 14;
  mm = 58;
  #else  
  Serial.println("Rele Clock");  
  #endif
  DateTime now = rtc.now();
  gettime(now, &mi, &ho); 
  pvmi = mi;
  pvho = ho;  
}

void loop() {    
  currtm = millis();  
  now = rtc.now();
  sprintf(orario, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
  gettime(now, &mi, &ho);
  
  //mi = now.minute();
  if (mi != pvmi) {
    stato_minuti = !stato_minuti;  
    digitalWrite(2, stato_minuti);
    Serial.println("MIN");
  }
  //ho = now.hour();
  if (ho != pvho) {
    if ((ho >= 7) && (ho <= 19)) {
      sequenza = (ho > 12 ? ho-12 : ho) * 2;  
      stato_ora = LOW;
      Serial.println("ORA");
    } else {
      Serial.println("ORA disabilitata");
    }
  }

  if (((currtm-t2) > 2000) && sequenza > 0){
    stato_ora = !stato_ora;  
    digitalWrite(3, stato_ora);
    Serial.print("SEQ:");
    Serial.println(sequenza);
    sequenza--;
    t2 = millis();
  }

  if ((currtm-t1) > 1000) {
    lcd.setCursor(0,0);
    lcd.print(orario);
    Serial.println(orario);
    t1 = millis();
  }

  #ifdef SIMULA
  //clock simulato
  if ((currtm-t3) > 5000) {
    updateclock();
    t3 = millis();
  }
  #endif

  //pulsanti setup ora/min
  btm = digitalRead(4);
  if (btm && !pbtm) {
    cambiaOra();    
  }
  pbtm = btm;
  
  bth = digitalRead(5);
  if (bth && !pbth) {
    cambiaMin();    
  }
  pbth = bth;


  pvmi = mi;
  pvho = ho;
}

#ifdef SIMULA
void updateclock(){
  mm++;
  if (mm >= 60) {
    mm = 0;
    hh++;
    if (hh >= 24) hh = 0;
  }  
  Serial.print(hh);
  Serial.print(":");
  Serial.println(mm);
}
#endif

void gettime(DateTime now, int *mi, int *ho){
  #ifdef SIMULA
  *mi = mm; 
  *ho = hh; 
  #else 
  *mi = now.minute();
  *ho = now.hour();
  #endif  
}

void cambiaOra() {
  Serial.println("h");
  int n = now.hour() + 1;
  if (n >= 24) n = 0;
  
  rtc.adjust(DateTime(now.year(), now.month(), now.day(), n, now.minute(), now.second()));

}
void cambiaMin() {
  Serial.println("m");
  int n = now.minute() + 1;
  if (n >= 60) n = 0;
  
  rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour(), n, now.second()));
}
