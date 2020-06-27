void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);

  Serial.begin(9600);

  digitalWrite(6, HIGH);
  delay(200);
  digitalWrite(6, LOW);
  delay(200);
  digitalWrite(12, HIGH);
  delay(200);
  digitalWrite(12, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);

  tone(5, 220);
  delay(100);
  tone(5, 440);
  delay(100);
  tone(5, 880);
  delay(300);
  noTone(5);
}

int stato = 0;

void loop() {
  
  if (digitalRead(2)) {
    Serial.println("D2");
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
  if (digitalRead(3)) {
    Serial.println("D3");
    digitalWrite(12, HIGH);
  } else {
    digitalWrite(12, LOW);  
  }

  int t = analogRead(A0);
  int l = analogRead(A1);
  Serial.print("trim=");
  Serial.print(t);
  Serial.print("\tlit=");
  Serial.println(l);

  analogWrite(6, map(t, 0, 1023, 0, 255));

  int v = analogRead(A1);
  int x = map(v, 0, 1024, 0, 255);
  analogWrite(9, x);
  analogWrite(10, x);
  analogWrite(11, x);
  
}
