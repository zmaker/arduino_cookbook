#include <SoftwareSerial.h>

int sendCommand(String cmd, String ans = "OK");

SoftwareSerial modem(3, 2);

void setup() {
  Serial.begin(115200);
  modem.begin(9600);
  Serial.println("term pronto\n");

  int n = sendCommand("AT");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT+CREG?", "OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT+CIPSHUT", "SHUT OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT+CGATT=1", "OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT+CSTT=\"TM\"", "OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT+CIICR", "OK");
  Serial.print("resp: ");Serial.println(n);
  delay(3000);
  n = sendCommand("AT+CIFSR", "OK");
  Serial.print("resp: ");Serial.println(n);
  
}

void loop() {
  if (modem.available()) {
    Serial.write(modem.read());  
  }
  if (Serial.available()) {
    modem.write(Serial.read());  
  }
}

int sendCommand(String cmd, String ans = "OK"){
  //invia il comando AT al modem
  Serial.print("->");Serial.println(cmd);
  modem.println(cmd);

  //timer per il timeout
  unsigned long t1 = millis();
  
  String line;
  while(true) {
    if (modem.available()) {
      char c = modem.read();
      //Serial.write(c);
      if (c == '\n') {
        Serial.print(">");Serial.println(line);
        //elaboro la linea
        if (line == ans) {
          Serial.print("trovato: ");Serial.println(ans);
          return 1;  
        } else if (line.indexOf("ERROR") >= 0) {
          Serial.print("trovato: errore!");
          return 0;  
        } else if ((ans == "*") && (line.length() > 0)) {
          Serial.print("any line");
          return 2;
        }
        line = "";
      } else if (c == '\r') {
        
      } else {
        line += c;
      }
    }
    //timeout
    if ((millis() - t1) > 10000l) {
      Serial.println("timeout modem");
      return -1;
    }
  }
}
