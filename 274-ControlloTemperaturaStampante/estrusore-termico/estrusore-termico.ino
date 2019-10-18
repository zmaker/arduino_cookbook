int th1 = 490;
int th2 = 495;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}

int stato = 0;
int t = 0;

void loop() {
  t = analogRead(A0);
  switch (stato) {
    case 0:
      startup();
      break;
    case 1:
      riscalda();
      break;
    case 2:
      raffredda();
      break;
  }
  Serial.print("t=");
  Serial.println(t);
  delay(100);
}

void startup() {
  digitalWrite(2, HIGH);
  stato = 1;  
  Serial.println("riscalda");
}

void riscalda() {  
  if (t >= th2) {
    digitalWrite(2, LOW);
    Serial.println("raffredda");
    stato = 2;
  }
}

void raffredda() {
  if (t <= th1) {
    digitalWrite(2, HIGH);
    Serial.println("riscalda");
    stato = 1;
  }
}
