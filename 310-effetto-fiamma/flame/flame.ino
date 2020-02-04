void setup(void) {
  randomSeed(A0);
}

unsigned long t1, dt;
int pausa = 10;

void loop(void) { 
  
  dt = millis() - t1;
  if (dt > pausa) {
    pausa = random(1, 30);
    t1 = millis();
    int x = random(50,255);  
    analogWrite(9, x); 
  }

}
