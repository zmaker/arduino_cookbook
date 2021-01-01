/*
  474 - sensore di forza
  - sensore in serie con resistenza da 10K e letto su A0
  - led con res da 390 sul pin 13
*/

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  int val = analogRead(A0);
 
  Serial.print("lettura = ");
  Serial.println(val);

  digitalWrite(13, (val > 200 ? HIGH : LOW)); 
  
  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2);
}
