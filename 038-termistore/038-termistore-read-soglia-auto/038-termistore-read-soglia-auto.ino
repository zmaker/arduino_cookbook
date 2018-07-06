int thr;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);

  //setup
  digitalWrite(13, HIGH);
  int v = analogRead(A0);
  delay(500);
  v += analogRead(A0);
  delay(500);
  v += analogRead(A0);
  delay(500);
  digitalWrite(13, LOW);

  thr = v / 3 + 4;
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
