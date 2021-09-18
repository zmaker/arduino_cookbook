/**
 * https://github.com/Arduino-IRremote/Arduino-IRremote
 */
#include <IRremote.h> 
#define IR_RECEIVE_PIN 2

int stato = 0;
int r, g, b;

void setup() {
  Serial.begin(9600); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  Serial.println("ok");
}


void loop() {
  int ircode = readIr();

  if (ircode != 0) Serial.println(ircode);

  switch (stato) {
    case 0:
      //OFF
      lampoff(ircode);
    break;
    case 1:
      //ON
      lampon(ircode);
    break; 
    case 2:
      lightup();
    break;
    case 3:
      lightdn();
    break;
  }

  applylight();
}

void lampoff(int cc){
  if (cc == 64) {
    r = 255;
    g = 255;
    b = 255;
    delay(100);
    stato = 1;
  }
}
void lampon(int cc){
  if (cc == 64) {
    r = 0;
    g = 0;
    b = 0;
    delay(500);
    stato = 0;
  } else if (cc == 70) {
    stato = 2;
  } else if (cc == 21) {
    stato = 3;
  }
}

void lightup() {
  r += 10;
  if (r >= 255) r = 255;
  g = r;
  b = r;
  stato = 1;
  delay(50);
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.println(" ");
}

void lightdn() {
  r -= 10;
  if (r <= 10) r = 10;
  g = r;
  b = r;
  stato = 1;
  delay(50);
  Serial.print(r);
  Serial.print("\t");
  Serial.print(g);
  Serial.print("\t");
  Serial.print(b);
  Serial.println(" ");
}

void applylight(){
  analogWrite(9, r);
  analogWrite(10, g);
  analogWrite(11, b);
}

int readIr() {
  int code = 0;
  if (IrReceiver.decode()) {
    code = IrReceiver.decodedIRData.command;
    if ((IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
         IrReceiver.resume();
         return;
    }   
    IrReceiver.resume();
  }  
  return code;
}
