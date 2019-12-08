#include <Wire.h>
#include "RTClib.h"

#define PIN_LAMP 3

// real time clock
DS1307 rtc;

unsigned long t1, dt1;

int th1_luce = 80;
int th2_luce = 60;

int mm, hh;
bool GIORNO;
bool LAMP;

int luce = 0;


void setup() {
  Serial.begin(9600);
 
  if (!rtc.begin()) {
    Serial.println("Errore! Verifica le connesioni dell'RTC!");
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

  pinMode(PIN_LAMP, OUTPUT);  //luce
  leggiOra();
  leggiLuce();
}

void loop() {
  /**
   * TIMER
   */
  dt1 = millis() - t1;
  if (dt1 >= 2000) {
    leggiLuce();
    leggiOra();
    t1 = millis();
  }

  //applico le azioni
  digitalWrite(PIN_LAMP, LAMP);
  
}

void leggiLuce() {
  for (int i = 0; i < 10; i++) {
    luce += analogRead(A0);
  }
  luce = luce / 10;
  luce = map (luce, 0, 1024, 0, 100);
    
  if (GIORNO) {  
    if (luce > th1_luce) {
      LAMP = LOW;
    } else if (luce < th2_luce) {
      LAMP = HIGH;
    }
  }
}

void leggiOra(){
  DateTime now = rtc.now();
  hh = now.hour();
  mm = now.minute();  
  
  if ((hh >= 6) && (hh < 22)) {
    GIORNO = true;
  } else {
    GIORNO = false;  
  }
  
}
