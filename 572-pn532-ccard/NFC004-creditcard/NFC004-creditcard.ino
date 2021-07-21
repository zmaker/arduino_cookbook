/*
 * librerie NDEF 
 * https://github.com/don/NDEF
 * e richiede anche
 * https://github.com/Seeed-Studio/PN532
*/
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

//display
#include <LiquidCrystal_I2C.h>

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


void setup(void) {
  pinMode(6, INPUT);  //ricarica
  pinMode(7, INPUT);  //buy
  pinMode(4, OUTPUT);  
  pinMode(5, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("NDEF Reader");
  nfc.begin();

  lcd.begin(16,2);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();  
  lcd.setCursor(0,0);
  lcd.print("CCard Reader"); 
}

int stato = 0;

void loop(void) {  
  if (nfc.tagPresent()) {    
    int credit = readCredit();
    lcd.setCursor(0,1);       
    lcd.print((credit > 0 ? credit : 0));
    lcd.print("  ");

    if (digitalRead(6)) {
      //ricarica
      writecard(100);  
    } else if (digitalRead(7)) {
      //buy
      int n = credit - 1;
      Serial.println(n);
      writecard(n);  
    }
  
  } else {
    lcd.setCursor(0,1);    
    lcd.print("         ");    
  }
}

void writecard(int n) {    
  digitalWrite(4, HIGH);
  if (nfc.tagPresent()) {    
    digitalWrite(5, HIGH);
    
    if (nfc.clean()) {
      Serial.println("clean");
      if (nfc.format()) {
        Serial.println("format");
        NdefMessage message = NdefMessage();
        String str = String(n);
        message.addTextRecord(str);
        if (nfc.write(message)) {
          Serial.println("write ok");      
        } else {
          Serial.println("write failed");      
        }
      } 
    }   
    digitalWrite(5, LOW);
  }
  digitalWrite(4, LOW);
}

int readCredit() {
  int n = -1;
  NfcTag tag = nfc.read();
  //String id = tag.getUidString();

  if (tag.hasNdefMessage()) {
    NdefMessage message = tag.getNdefMessage();
    int recordCount = message.getRecordCount();
    if (recordCount == 1) {
      NdefRecord record = message.getRecord(0);
      int payloadLength = record.getPayloadLength();
      byte payload[payloadLength];
      record.getPayload(payload);

      String data = "";
      for (int c = 0; c < payloadLength; c++) {
        data += (char)payload[c];
      }
      Serial.print("DATA:");
      Serial.print(data);
      Serial.println("#");      
      if (payloadLength > 3) { //devo togliere: ".en"
         data = data.substring(3); 
      }
      Serial.println(payloadLength);
      Serial.println(data);
      n = data.toInt();
      Serial.print("n:");
      Serial.print(n);
      Serial.println("#");      
    }
  }
  return n;  
}
