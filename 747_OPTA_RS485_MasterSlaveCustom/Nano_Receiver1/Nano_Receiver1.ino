#include <SoftwareSerial.h>

SoftwareSerial RS485Serial(10, 11); //RX, TX
int stato = 0;
uint8_t buff[4];
int ib = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("RS485 slave");

  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(3, LOW);
  
  RS485Serial.begin(4800);
}

void loop() {
  switch(stato) {
    case 0:
      if (RS485Serial.available()) {
        buff[ib] = RS485Serial.read();
        ib++;
        if (ib >= 4) {
          ib = 0;
          stato = 1;  
        }
      }
      break;
    case 1:
      Serial.print(buff[0], HEX);
      Serial.print(" ");
      Serial.print(buff[1], HEX);
      Serial.print(" ");
      Serial.print(buff[2], HEX);
      Serial.println(" ");

      //elaboro
      if (buff[0] == 10) {
        if (buff[1] == 1) {
          digitalWrite(4, buff[2]);
        }   
      }

      digitalWrite(3, HIGH);
      RS485Serial.write(0x01);
      digitalWrite(3, LOW); 
      stato = 0;     
      break;
  }

}
