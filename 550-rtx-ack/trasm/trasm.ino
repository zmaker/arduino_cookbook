#include <SoftwareSerial.h>

SoftwareSerial port(10, 11); // RX, TX
unsigned long t1, dt;
int stato = 0;

void setup() {
  Serial.begin(9600);
  port.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.println("trasmettitore"); 
}

void loop() {
  switch(stato) {
    case 0:
      tx();
      break;
    case 1:
      ack();
      break;  
    case 2:
      timeout();
      break;  
  }
}

void tx() {
  Serial.println("TX");
  port.write('a');
  digitalWrite(13, HIGH);  
  stato = 1;    
  t1 = millis();
}

bool FIRST = true;

void ack() {  
  if (FIRST) {
    Serial.println("RX...");
    FIRST = false;
  }
  if (port.available()) {
    char c = port.read();
    if (c == 'k') {
      Serial.println("ACK");
      port.flush();
      digitalWrite(13, LOW);
      delay(500);
      stato = 0;   
    }    
  } 
  dt = millis() - t1;
  if (dt > 5000) {
    //timeout!
    Serial.println("timeout");
    stato = 2;
  } 
}
void timeout() {
  digitalWrite(13, LOW); 
  digitalWrite(12, HIGH); 
  stato = 0;
  delay(3000);
  digitalWrite(12, LOW);  
}
