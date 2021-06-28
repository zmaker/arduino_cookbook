#include <SoftwareSerial.h>

SoftwareSerial sim800(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  sim800.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  sim800.println("AT"); 
  updateSerial();
  
  sim800.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  sim800.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}

int n = 0; 
String ret = "";
bool LOOP = true;
  
void loop() {
  if (sim800.available()) {
      char c = sim800.read();
      if (c == '\n') {
        Serial.println("RX:" + ret + "#");                
        if (ret == "ledon") {
          digitalWrite(13, HIGH);
          Serial.println("on");
        } else if (ret == "ledoff") {
          digitalWrite(13, LOW);
          Serial.println("off"); 
        }
        ret = "";
      } else if (c == '\r') {        
      } else {
        ret += c;                 
      }    
    }
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    sim800.write(Serial.read());
  }
  while(sim800.available()) {
    Serial.write(sim800.read());
  }
}
