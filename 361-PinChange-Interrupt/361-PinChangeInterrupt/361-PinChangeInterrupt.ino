#include <PinChangeInt.h>
 
volatile int tick = 0; 
 
void setup() {
  Serial.begin(9600);
  
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  
  PCintPort::attachInterrupt(7, tickup, RISING);
  PCintPort::attachInterrupt(8, tickdown, RISING); 
}

void loop() {
  Serial.print("tickcount:\t");
  Serial.println(tick, DEC);
  delay(1000);
  
}
 
void tickup() {
  tick++;
}

void tickdown() {
  tick--;
}
