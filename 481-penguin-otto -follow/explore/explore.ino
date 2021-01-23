#include <Otto9.h>
Otto9 Otto;  

#define PIN_YL 10  //left leg
#define PIN_YR 9   //right leg
#define PIN_RL 12  //left foot
#define PIN_RR 6   //right foot
#define PIN_Trigger  5  //TRIGGER pin (8)
#define PIN_Echo     4  //ECHO pin (9)
#define PIN_Buzzer  A2 //BUZZER pin (13)

#define OTTO_FWD 1
#define OTTO_BACK -1

void setup(){
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger, PIN_Echo);  
  Otto.home();
  delay(500);
  Serial.begin(9600);
}

int vel = 1000; //da 600 a 1400

int left, prev_left;
int right, prev_right;

void loop() {
  //avanzo di 2 passi
  Otto.walk(2, vel, OTTO_FWD);

  //valuto la distanza
  int distance = Otto.getDistance(); 
  Serial.println(distance);
  if (distance < 20) {    
    //se trovo un ostacolo
    Otto.walk(4, vel, OTTO_BACK);  //BACK o FWD 
    Otto.turn(5, vel, 1);//ruota di 5 passi a SX
    Otto.home();
  }   
  left = analogRead(A0);     
  if (( left > 1000) && (prev_left > 1000)) {
    Serial.println("LEFT");
    Otto.walk(4, vel, OTTO_BACK);  
    Otto.turn(4,vel,1);//4 steps turning LEFT    
  }
  prev_left = left;

  left = analogRead(A1);     
  if (( right > 1000) && (prev_right > 1000)) {
    Serial.println("RIGHT");
    Otto.walk(4, vel, OTTO_BACK);  
    Otto.turn(4,vel,-1);//4 steps turning RIGHT
  }     
  prev_right = right;  

  delay(100);
}
