#include <Otto9.h>
Otto9 Otto;

#define PIN_YL 10
#define PIN_YR 9
#define PIN_RL 12
#define PIN_RR 6
#define PIN_Trigger  5  
#define PIN_Echo  4  
#define PIN_Buzzer  A2

#define OTTO_FWD 1
#define OTTO_BACK -1

int vel = 1000;  //600 a 1400

void setup() {
  Serial.begin(9600);
  Otto.init(PIN_YL, PIN_YR, PIN_RL, PIN_RR, true, A6, PIN_Buzzer, PIN_Trigger, PIN_Echo);
  Otto.home();
  delay(500);
  Otto.walk(2, vel, OTTO_FWD);
  delay(1000);
  Otto.walk(2, vel, OTTO_BACK);
  Otto.home();

  delay(3000);
  Otto.turn(2, vel, 1); 
  Otto.turn(2,1000,-1);
  Otto.home();
  delay(100);            
  
          Otto.bend (1,500,1); //usually steps =1, T=2000
          Otto.bend (1,2000,-1);     
          Otto.shakeLeg (1,1500, 1);
          Otto.home();
          delay(100);
          Otto.shakeLeg (1,2000,-1);
          Otto.moonwalker(3, 1000, 25,1); //LEFT
          Otto.moonwalker(3, 1000, 25,-1); //RIGHT  
          Otto.crusaito(2, 1000, 20,1);
          Otto.crusaito(2, 1000, 20,-1);
          delay(100); 
          Otto.flapping(2, 1000, 20,1);
          Otto.flapping(2, 1000, 20,-1);
          delay(100);        
          Otto.swing(2, 1000, 20);
          Otto.tiptoeSwing(2, 1000, 20);
          Otto.jitter(2, 1000, 20); //(small T)
          Otto.updown(2, 1500, 20);  // 20 = H "HEIGHT of movement"T 
          Otto.ascendingTurn(2, 1000, 50);
          Otto.jump(1,2000);
        

}

void loop() {
  int distance = Otto.getDistance();
  Serial.println(distance);
}
