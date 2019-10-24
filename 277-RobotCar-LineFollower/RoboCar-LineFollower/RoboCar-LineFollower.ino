#include "robot.h"

#define SENS_DX 10
#define SENS_MID 4
#define SENS_SX 2
#define LED 13

void setup() {
  Serial.begin(9600);
  pinMode(SENS_DX, INPUT);
  pinMode(SENS_MID, INPUT);
  pinMode(SENS_SX, INPUT);

  pinMode(LED, OUTPUT);
}

void loop() {
  int dx = !digitalRead(SENS_DX);
  int mx = !digitalRead(SENS_MID);
  int sx = !digitalRead(SENS_SX);

  if (mx == HIGH) digitalWrite(LED, HIGH);
  else digitalWrite(LED, LOW);
  
  Serial.print(sx);
  Serial.print("\t");
  Serial.print(mx);
  Serial.print("\t");
  Serial.print(dx);
  Serial.print("\n");

  if (mx){
    forward();
  }
  else if (dx) {
    right();
    
  }
  else if (sx) {
    left();
    
  }
  if ((mx == 0) && (sx == 0) && (dx == 0)) {
    stop();  
  }
}
