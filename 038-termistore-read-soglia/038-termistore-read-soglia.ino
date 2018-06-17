int thr = 37;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int v = analogRead(A0);
  Serial.println(v);

  digitalWrite(13, LOW);
  
  if (v > thr) {
    digitalWrite(13, HIGH);  
  } 

  delay(50);

}
