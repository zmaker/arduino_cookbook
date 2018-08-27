#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"


SMSGSM sms;

boolean started = false;

void setup() {
    Serial.begin(9600);
    Serial.println("GSM Shield testing.");
    if (gsm.begin(4800)) {
        Serial.println("\nstatus=READY");
        started=true;
    } else { 
        Serial.println("\nstatus=IDLE");
    }
}

char phone_number[20]; // array for the phone number string
char sms_text[100];

void loop() {
    if(started) {
        char sms_position = sms.IsSMSPresent(SMS_UNREAD);
        if (sms_position) {            
            Serial.print("SMS postion:");
            Serial.println(sms_position,DEC);
            sms.GetSMS(sms_position, phone_number, sms_text, 100);
            Serial.println(phone_number);
            Serial.println(sms_text);
        } else {
            Serial.println("NO NEW SMS,WAITTING");
        }     
        delay(1000);
    }

   /*
    * 
         //if NO SPACE ,you need delte SMS  from position 1 to position 20
       //please enable this four lines
       for(i=1;i<=20;i++) {
           sms.DeleteSMS(i);
       }
  */
}
