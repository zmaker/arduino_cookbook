void stato0();
void stato1();
void stato2();

typedef void (*fDiStato) ();

fDiStato stati[] = {stato0, stato1, stato2};

int stato = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  stati[stato]();
}

void stato0(){
  Serial.println("s0");
  delay(1000);
  stato = 1;
}

void stato1(){
  Serial.println("s1");
  delay(1000);
  stato = 2;
}
void stato2(){
  Serial.println("s2");
  delay(1000);
  stato = 0;
}
