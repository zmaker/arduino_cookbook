#include <SoftwareSerial.h>
/*
per leggere l'ora dalla rete
AT+CCLK?

La prima volta:
at+clts=1
at&W

*/

SoftwareSerial modem(6, 7); //RX, TX

void setup() {
  Serial.begin(9600);
  modem.begin(9600);
  delay(100);
  pinMode(9, OUTPUT);

  digitalWrite(9, LOW);
  delay(100);
  digitalWrite(9, HIGH);
  delay(100);
  digitalWrite(9, LOW);
  delay(100);

  Serial.println("SIM800: ");

  modem.println("AT+CCLK?");

  bool LOOP = 1;
  String line = "";
  String strtime = "";
  while(LOOP) {
    if (modem.available()) {
      char c = modem.read();
      if (c == '\n') {
        //Serial.print(">");
        //Serial.println(line);

        if (line.indexOf("+CCLK:") >= 0) {
          strtime = line.substring(8, line.length()-4);
        }
        
        if (line.length() == 0) {
          LOOP = 0;
          Serial.println("END");
        } 

        line = "";
      } else if (c != '\r') {
        line += c;
      }  
    }
  }
  Serial.println("--------");
  Serial.println(strtime);
  const char* datat = strtime.c_str();
  int hh, mi, ss, yy, mm, dd;
  sscanf(datat, "%02d/%02d/%02d,%02d:%02d:%02d", 
    &yy, &mm, &dd, &hh, &mi, &ss);
  Serial.print(hh);Serial.print("/");
  Serial.print(mi);Serial.print("/");
  Serial.print(ss);Serial.print("\n");
}

void loop() {
  if (modem.available()) {
     char c = modem.read();
     Serial.write(c);
  }
  if (Serial.available()) {
     char c = Serial.read();
     modem.write(c);
  }
}
