void setup() {
  Serial.begin(9600);
}

void loop() {  
  int x = analogRead(A0);
  int y = analogRead(A1);
  int z = analogRead(A2);
/*
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("\ty: ");
  Serial.print(y);
  Serial.print("\tz: ");
  Serial.println(z);
*/
  int r = map(x, 200,400, 0,255);
  int g = map(y, 100,400, 0,255);
  int b = map(z, 100,400, 0,255);

  analogWrite(3, r);
  analogWrite(5, g);
  analogWrite(6, b); 
  
  delay(10);
}
