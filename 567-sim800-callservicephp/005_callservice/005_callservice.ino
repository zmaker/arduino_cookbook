/*
 * 
 * https://predictabledesigns.com/the-sim800-cellular-module-and-arduino-a-powerful-iot-combo/
 */

#include <SoftwareSerial.h>

SoftwareSerial sim800(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2


void setup() {
  pinMode(4, INPUT);
  
  Serial.begin(9600);
  sim800.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);
  sim800.println("AT"); //Once the handshake test is successful, it will back to OK
  //updateSerial();
  resp("OK");
  sim800.println("AT+CSQ"); //test segnale
  resp("OK");
  sim800.println("AT+CFUN=1"); //full funzioni
  resp("OK");  
  sim800.println("AT+CGATT=1"); //collegati a gprs
  resp("OK");
  sim800.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  resp("OK");
  sim800.println("AT+SAPBR=3,1,\"APN\",\"TM\"");
  resp("OK");
  sim800.println("AT+SAPBR=1,1");
  resp("OK");
  sim800.println("AT+HTTPINIT"); //Init HTTP service
  resp("OK");
  sim800.println("AT+HTTPPARA=\"CID\",1");
  resp("OK");
  sim800.println("AT+HTTPPARA=\"REDIR\",1"); //Auto redirect
  resp("OK");  
}

void loop() {
  if (digitalRead(4) ) {
    int v = analogRead(A0);
    sim800.println("AT+HTTPPARA=\"URL\",\"http://www.zeppelinmaker.it/service.php?sens="+String(v)+"\"");
    resp("OK");    
    sim800.println("AT+HTTPACTION=0");  //call
    resp("OK");
    delay(5000);
    sim800.println("AT+HTTPREAD");    
    resp("OK");
  }
}

int resp (String txt) {   
  int n = 0; 
  String ret = "";
  bool LOOP = true;
  while(LOOP){
    
    if (sim800.available()) {
      char c = sim800.read();
      if (c == '\n') {
        Serial.println("RX:" + ret + "#");
        if (ret == txt) {
          Serial.println("---");
          LOOP = false;
          n = 1;
        } else if (ret == "OK") {
          LOOP = false;
          n = 0;
        } else if (ret == "ERROR") {
          LOOP = false;
          n = -1;
        }
        
        ret = "";
      } else if (c == '\r') {        
      } else {
        ret += c;                 
      }    
    }
  }
  delay(1000);
  return n;
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(sim800.available()) 
  {
    Serial.write(sim800.read());//Forward what Software Serial received to Serial Port
  }
}
