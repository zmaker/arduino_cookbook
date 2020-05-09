static byte ena = 6;
static byte stp = 4;
static byte dir = 5;
int ts = 10;
int fdir = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(12, OUTPUT); //dir led
  pinMode(13, OUTPUT); //step led
  pinMode(stp, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(ena, OUTPUT);
  digitalWrite(stp, HIGH);
  digitalWrite(dir, HIGH);
  digitalWrite(ena, LOW);
  Serial.println("ok");
}

void loop() {
  if (digitalRead(3) == HIGH) {
    fdir = !fdir;
    Serial.print("dir: ");
    Serial.println(fdir);
    digitalWrite(dir, fdir);
    digitalWrite(12, fdir);
    delay(300);
  }
  if (digitalRead(2) == HIGH) {
     Serial.println("run");
     digitalWrite(ena, HIGH);
     delay(100);
     for (int i = 0; i < 100; i++) {
       dostep();
       Serial.print(".");
     }
     digitalWrite(ena, LOW);
     Serial.println("end");
  }
}

void dostep(){
  digitalWrite(stp, LOW);
  digitalWrite(13, HIGH);
  delay(ts);
  digitalWrite(stp, HIGH);
  digitalWrite(13, LOW);
  delay(ts);
}
