#include <SoftwareSerial.h>

SoftwareSerial modem(3, 2); //RX, TX

int sendCommand(String cmd, String ans = "OK");

void setup() {
  Serial.begin(9600);
  modem.begin(9600);

  int n = sendCommand("AT");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT1", "OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT2", "PAGE: OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT3", "OK");
  Serial.print("resp: ");Serial.println(n);
  n = sendCommand("AT4", "OK");
  Serial.print("resp: ");Serial.println(n);  
  n = sendCommand("AT5", "OK");
  Serial.print("resp: ");Serial.println(n);  
  n = sendCommand("AT2", "*");
  Serial.print("resp: ");Serial.println(n);
  
}

void loop() {
  if (Serial.available()) {
    modem.write(Serial.read());  
  }
  if (modem.available()) {
    Serial.write(modem.read());  
  }
}

int sendCommand(String cmd, String ans = "OK"){
  Serial.print("-> ");Serial.println(cmd);
  modem.println(cmd);
  
  String line;
  unsigned long t1 = millis();

  while(true) {
    //timeout
    if ((millis() - t1) > 5000l) {
      Serial.print("timeout");
      return -1;  
    }
    
    if (modem.available()) {
      char c = modem.read();
      if (c == '\n') {
        Serial.print("line: ");Serial.println(line);
        //elaboro line
        if (line == ans) {
          Serial.print("trovato: ");Serial.println(ans);
          return 1;  
        } else if (line.indexOf("ERROR") >= 0) {
          Serial.println("trovato: errore!");
          return 0;  
        } else if ((ans == "*") && (line.length() > 0)) {
          Serial.println("any line");
          return 2;
        }

        line = "";
      } else if (c != '\r') 
        line += c;  
      }
    }
    return 0;
 }

 
