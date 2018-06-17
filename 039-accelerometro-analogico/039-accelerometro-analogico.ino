void setup() {
  Serial.begin(9600);
}

void loop() {  
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);

  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.print(y);
  Serial.print("\tz: ");
  Serial.println(z);
  
  delay(100);
}
