#include <SoftwareSerial.h>

SoftwareSerial rs485(10, 11); //RX, TX

uint8_t buff[4];
int ib = 0;
 
void setup() {
  Serial.begin(115200);
  Serial.println("RS485 RX");

  pinMode(4, OUTPUT); //led1
  pinMode(5, OUTPUT); //led2
  
  pinMode(3, OUTPUT); //RTX
  digitalWrite(3, LOW);
  
  rs485.begin(4800);

  while (rs485.available()) {
    Serial.write(rs485.read());  
  }
}

void loop() {
  while (rs485.available()) {
    buff[ib] = rs485.read();
    ib++;
    if (ib >= 4) {
      ib = 0;
      Serial.print(buff[0], HEX);
      Serial.print(" ");
      Serial.print(buff[1], HEX);
      Serial.print(" ");
      Serial.print(buff[2], HEX);
      Serial.print("\n");

      if (buff[0] == 10) { //controllo addr
        if (buff[1] == 4) {
          digitalWrite(4, buff[2]);
        }
        if (buff[1] == 5) {
          digitalWrite(5, buff[2]);
        }
      }
        
    }  
  }
  
}
