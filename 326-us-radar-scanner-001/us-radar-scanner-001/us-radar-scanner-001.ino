#include <Servo.h>  

Servo myservo;      
int Echo = A4;  
int Trig = A5; 

void setup() {
  myservo.attach(3);
  Serial.begin(9600);    
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);   
  Serial.println("Ok");
}

void loop() {
  Serial.println("Scan");
  myservo.write(90);
  for (int i = 45; i < 135; i = i + 5) {
    myservo.write(i);
    int d = readDistanza();
    delay(100);
    Serial.println(d);
  }
  myservo.write(90);
  delay(500);
}

int readDistanza() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float d = pulseIn(Echo, HIGH);  
  d = d / 58;       
  return (int)d;
}  
