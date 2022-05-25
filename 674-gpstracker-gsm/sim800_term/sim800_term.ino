#include <SoftwareSerial.h>

//MODEM
SoftwareSerial modem(2, 3); //RX, TX

void setup() {
  Serial.begin(9600);
  
  modem.begin(9600);
  Serial.println("\nOK:");
  /*
  modem.println("AT");
  int n = getResponse("OK", &modem);
  */
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
/*
int getResponse(String txt, Stream *ser) {   
  int n = 0; 
  String ret = "";
  bool LOOP = true;
  while(LOOP){
    //if (ser->available()) {
    if (modem.available()) {
      //char c = ser->read();
      char c = modem.read();
      Serial.write(c);
      if (c == '\n') {          
        if (ret.equals(txt)) {
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
  return n;
}
*/
