void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);

  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
}

unsigned long t1, dt;
int p = 100;
int st, pst;

void loop() {
  st = digitalRead(5);
  if (st && !pst) {
    dir(3);  
  } 
  pst = st;
  
  dt = millis() - t1;
  if (dt > p) {
    p = map( analogRead(A0), 0, 1024, 1, 100 );
    toggle(2);
    t1 = millis();  
  }

}

void toggle(int pin) {
  static int s = LOW;
  digitalWrite(pin, s);
  s = !s;  
}

void dir(int pin) {
  static int s = HIGH;
  digitalWrite(pin, s);
  s = !s;  
}
