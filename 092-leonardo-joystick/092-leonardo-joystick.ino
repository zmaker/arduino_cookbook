#include <Mouse.h>

#define BUTTON 7

void setup() {
  pinMode(BUTTON, INPUT);  
  Serial.begin(9600);
  Mouse.begin();
}

int stato = LOW;

void loop() {
  if (digitalRead(BUTTON)) {
    stato = !stato;
    delay(300);
  }

  if (stato) {
    int x = analogRead(A0);
    int y = analogRead(A1);
    String str = "x: " + String(x) + " y: " + String(y);
    x = map(x, 0,1024, -10, 10);
    y = map(y, 0,1024, -10, 10);
    Mouse.move(x,y, 0);    
    Serial.println(str);
    delay(100);
  }
}
