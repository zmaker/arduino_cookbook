#include <SoftwareSerial.h>

SoftwareSerial port(10, 11); // RX, TX
int stato = 0;

void setup() {
  Serial.begin(9600);
  port.begin(9600);
  pinMode(2, OUTPUT); 
  Serial.println("ricevitore"); 
}

void loop() {
  switch(stato) {
    case 0:
      recv();
      break;
    case 1:
        ack();
      break;  
  }
}

void recv() {
  if (port.available()) {
    char c = port.read();
    Serial.print(c);
    if (c == 'a') {
      Serial.println("rx");
      digitalWrite(2, HIGH);
      delay(500);
      digitalWrite(2, LOW);
      port.flush();
      stato = 1;   
    }    
  }
}

void ack() {
  delay(1000);
  port.write('k');
  digitalWrite(2, LOW);
  Serial.println("ack");
  stato = 0;  
}
