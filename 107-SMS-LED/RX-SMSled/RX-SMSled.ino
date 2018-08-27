#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"

SMSGSM sms;

boolean started = false;

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    Serial.println("GSM Shield testing.");
    if (gsm.begin(4800)) {
        Serial.println("\nstatus=READY");
        started = true;
    } else { 
        Serial.println("\nstatus=IDLE");
    }
}

char phone_number[20];
char sms_text[100];

void loop() {
    if (started) {
        char sms_position = sms.IsSMSPresent(SMS_UNREAD);
        if (sms_position) {            
            sms.GetSMS(sms_position, phone_number, sms_text, 100);            
            Serial.println(sms_text);
            String msg = String(sms_text);
            if (msg.indexOf("Ledon") >= 0) {
              Serial.println("ON");
              digitalWrite(13, HIGH);
            }
            if (msg.indexOf("Ledoff") >= 0) {
              Serial.println("OFF");
              digitalWrite(13, LOW);
            }
            
        }     
        delay(1000);
    }
}
