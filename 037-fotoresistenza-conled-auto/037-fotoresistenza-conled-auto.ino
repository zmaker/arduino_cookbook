int thr;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  int v = analogRead(A0);
  thr = v + 50;
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);

  if (v > thr) {
    digitalWrite(13, HIGH);  
  } else {
    digitalWrite(13, LOW);  
  }
  
  delay(100);
}
