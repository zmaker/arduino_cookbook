#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

#define BT 13

SMSGSM sms;

boolean started=false;

void setup() {
    pinMode(BT, INPUT);
    Serial.begin(9600);
    Serial.println("GSM Shield testing.");

    if (gsm.begin(4800)) {
        Serial.println("\nstatus=READY");
        started=true;
    } else { 
        Serial.println("\nstatus=IDLE");
    }
}

void loop() {

  if (digitalRead(BT)) {
    if(started) {
        Serial.println("invio sms...");
        if (sms.SendSMS("3791153108", "SMS da Arduino!")) {
          Serial.println("\nSMS sent OK");
        }
       
    }  
    delay(300);
  }
}
