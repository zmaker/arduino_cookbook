#include "robot.h"
#include <Servo.h>  

Servo myservo;      

int rightDistance = 0;
int leftDistance = 0;
int middleDistance = 0;

void setup() {
  myservo.attach(3);
  Serial.begin(9600);    
  pinMode(Echo, INPUT);    
  pinMode(Trig, OUTPUT);   
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  stop(); 
}

int MINDIST = 10;

void loop() {
  myservo.write(90);
  delay(500);
  middleDistance = Distance_test();

  if (middleDistance < MINDIST) {
    stop();
    delay(500);
    myservo.write(10);
    delay(1000);
    rightDistance = Distance_test();

    delay(500);
    myservo.write(90);
    delay(1000);
    myservo.write(170);
    delay(1000);
    leftDistance = Distance_test();

    delay(500);
    myservo.write(90);
    delay(1000);

    if (rightDistance > leftDistance) {
      right();
      delay(500);  
    } else if (rightDistance < leftDistance) {
      left();
      delay(500);  
    } else if ( (rightDistance <= MINDIST) || (leftDistance <= MINDIST) ) {
      back();
      delay(500);
    } else {
      forward();  
    }
    
  } else {
    forward();
  }
}


