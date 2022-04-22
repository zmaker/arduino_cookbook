#include <SoftwareSerial.h>

//MODEM
#define SER_TX 2
#define SER_RX 3
SoftwareSerial modem(SER_RX, SER_TX);

int resp (String txt = "OK");
void sendCommand(Stream *ser, String cmd, String ans = "OK", int tryon = 3);
String getPage(Stream *ser);

void setup() {
  Serial.begin(9600);
  //il modem deve inizializzarsi
  for (int i = 0; i < 5; i++) {
    delay(100);
    Serial.print(".");
  }
  modem.begin(9600);
  Serial.println("\nOK:");

  int n = 0;
  sendCommand(&modem, "AT");
  sendCommand(&modem, "AT+SAPBR=3,1,\"APN\",\"TM\"");  
  sendCommand(&modem, "AT+SAPBR=0,1");
  sendCommand(&modem, "AT+SAPBR=1,1");
  sendCommand(&modem, "AT+HTTPINIT");
  sendCommand(&modem, "AT+HTTPPARA=\"CID\",1");
  sendCommand(&modem, "AT+HTTPPARA=\"REDIR\",1");

  //SOLO HTTP
  String url = "http://www.zeppelinmaker.it/helloworld.txt";
  //String url = "http://www.zeppelinmaker.it/service-conf.php?id=123435";
  sendCommand(&modem, "AT+HTTPPARA=\"URL\",\""+url+"\"");
  sendCommand(&modem, "AT+HTTPACTION=1", "+HTTPACTION:");
  //sendCommand(&modem, "AT+HTTPREAD"); 
  String page = getPage(&modem); 
  sendCommand(&modem, "AT+HTTPTERM");  

  Serial.print("DATA: ");Serial.println(page);
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

void sendCommand(Stream *ser, String cmd, String ans = "OK", int tryon = 3){  
  int n = 0;
  int tentativi = 0;
  do {
    delay(1000);
    Serial.print("\nSEND: ");Serial.println(cmd);
    ser->println(cmd);      
    n = resp(ans);   
    Serial.print("\nRET : ");Serial.println(n); 
    tentativi++;
  } while ((n < 0) && (tentativi <  tryon));   
}

String getPage(Stream *ser) {
  String line = "";
  String page = "";
  int stpage = 0;
  bool LOOP = true;
  int n = 0;
  ser->println("AT+HTTPREAD");
  while(LOOP) {
    if (ser->available()) {
      char c = ser->read();      
      //Serial.write(c);    
      if (c == '\n') {
        switch(stpage) {
          case 0:
            //cerco +HTTPREAD: 
            if (line.indexOf("+HTTPREAD:") >= 0) stpage = 1;
            break;
          case 1:
            //line contiene la pagina (1 sola riga)
            if (line.indexOf("OK") >= 0) {
              LOOP = false;
            } else {
              page += line + "\n";             
            }
            break;
        }               
        line = ""; 
      } else if (c != '\r') {
        line += c;
      }      
    }
  }  
  return page;
}

int resp (String txt = "OK") {   
  int n = 0; 
  String line = "";
  int rows = 0;
  while (true) {
    if (modem.available()) {
      char c = modem.read();
      //Serial.write(c);
      if (c == '\n') {
        rows++;
        Serial.print("->|");Serial.print(line);Serial.print("|(");
        Serial.print(line.length());Serial.println(")");
        //Serial.print("rows:");Serial.println(rows);
        if (line.indexOf(txt) >= 0) {
          //Serial.print("trovato:");Serial.println(txt);
          n = 1;
          break; 
        } else if (line.equals("ERROR")) {
          n = -1;
          break; 
        }
        line = "";
      } else if (c == '\r') {        
      } else {
        line += c;                 
      } 
    }   
  }
  return n;
}
