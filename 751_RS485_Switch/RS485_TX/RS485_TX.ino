#include <SoftwareSerial.h>

SoftwareSerial rs485(10, 11); //RX, TX

uint8_t dati[4];

int bt1, pvbt1;
int bt2, pvbt2;
int led1, led2;

 
void setup() {
  Serial.begin(115200);
  Serial.println("RS485 TX");

  pinMode(2, INPUT); //BT1
  pinMode(4, INPUT); //BT2
  
  pinMode(3, OUTPUT); //RTX

  rs485.begin(4800);
}

void loop() {
  bt1 = digitalRead(2);
  bt2 = digitalRead(4);

  if (!bt1 && pvbt1) {
    led1 = !led1;
    Serial.println("Invio comando 1"); 
    digitalWrite(3, HIGH);
    delay(1);
    dati[0] = 10; //addr
    dati[1] = 4;  //fun
    dati[2] = led1;   //val
    dati[3] = 0;
    rs485.write(dati, sizeof(dati));
    delay(1);
    digitalWrite(3, LOW);
  }

  if (!bt2 && pvbt2) {
    led2 = !led2;
    Serial.println("Invio comando 2"); 
    digitalWrite(3, HIGH);
    delay(1);
    dati[0] = 10; //addr
    dati[1] = 5;  //fun
    dati[2] = led2;   //val
    dati[3] = 0;
    rs485.write(dati, sizeof(dati));
    delay(1);
    digitalWrite(3, LOW);
  }
  
  pvbt1 = bt1;  
  pvbt2 = bt2;
}
