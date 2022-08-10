#include "JoyShield.h"

int x, y, px, py;

void setup() {
  Serial.begin(9600);
  
  pinMode(BT_UP, INPUT_PULLUP);
  pinMode(BT_DN, INPUT_PULLUP);
  pinMode(BT_DX, INPUT_PULLUP);
  pinMode(BT_SX, INPUT_PULLUP);
  pinMode(BT_E, INPUT_PULLUP);
  pinMode(BT_F, INPUT_PULLUP);
  pinMode(BT_MID, INPUT_PULLUP);

}

void loop() {
  if (!digitalRead(BT_UP)) {
    Serial.println("UP");
    delay(100);  
  }
  if (!digitalRead(BT_DN)) {
    Serial.println("DN");
    delay(100);  
  }
  if (!digitalRead(BT_DX)) {
    Serial.println("DX");
    delay(100);  
  }
  if (!digitalRead(BT_SX)) {
    Serial.println("SX");
    delay(100);  
  }
  if (!digitalRead(BT_E)) {
    Serial.println("E");
    delay(100);  
  }
  if (!digitalRead(BT_F)) {
    Serial.println("F");
    delay(100);  
  }
  if (!digitalRead(BT_MID)) {
    Serial.println("MID");
    delay(100);  
  }
  
  x = analogRead(AXIS_X);
  y = analogRead(AXIS_Y);
  if ((abs(x-px) > 3) || (abs(y - py) > 3)){
    Serial.print(x);Serial.print("\t");
    Serial.println(y);
  }

  px = x;
  py = y;
}
