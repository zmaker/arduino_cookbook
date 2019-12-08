#include <Servo.h> 

Servo myservo;

void setup() {
  Serial.begin(115200);
   
  myservo.attach(9);
  
} 

int v = 0;

void loop() {
  v = analogRead(A0);
  myservo.writeMicroseconds(map(v, 0, 1024, 1000, 2000));
  Serial.println(v); 
} 
