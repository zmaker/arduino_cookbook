void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);
  x = map(x, 280, 440, 0, 100);
  y = map(y, 280, 440, 0, 100);
  z = map(z, 280, 440, 0, 100);

  int mod = sqrt(x*x + y*y + z*z);

  int note = map(mod, 50, 120, 50, 400);

  tone(8, note, 50);
  delay(50);
  
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.print(z);
  Serial.print("\t");
  Serial.print(mod);
  Serial.print("\t");
  Serial.print(note);
  Serial.print("\n");
  //delay(100);
  
}
