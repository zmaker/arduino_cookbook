void setup() {
  DDRB = B00100000; 

  //per gli ingressi PINB
  Serial.begin(9600);
}

long t;

void loop() {
  t = micros();
  PORTB = B00100000;
  delay(500);
  PORTB = B00000000;
  delay(500);
  t = micros() - t;
  Serial.print(t);
  Serial.print(" ");
  
  t = micros();
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  t = micros() - t;
  Serial.println(t);
}
