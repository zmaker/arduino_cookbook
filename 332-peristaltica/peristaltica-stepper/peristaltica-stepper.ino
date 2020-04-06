void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

int run = LOW;
int dir = LOW;
int step = LOW;
int vel;

void loop() {
 if (digitalRead(2)) {
   run = !run;
   delay(300); 
   digitalWrite(9, !run);
 }  

 if (digitalRead(3)) {
   dir = !dir;
   digitalWrite(10, dir);
   delay(300);
 }
 
 if (run) {
   vel = map(analogRead(A0), 0, 1024, 1, 100);
   digitalWrite(11, step);
   delay(vel);
   step = !step; 
 }

}
