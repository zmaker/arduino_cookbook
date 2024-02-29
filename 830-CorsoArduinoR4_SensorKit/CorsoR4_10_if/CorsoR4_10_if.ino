void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
}

void loop() {
  //lettura analogica da 0 a 1023
  int pot = analogRead(A0);
  //stampo il valore analogico
  Serial.println(pot);

  if ( pot > 512 ) {
    digitalWrite(3, HIGH);
  } else {
    digitalWrite(3, LOW);
  }
  delay(100);
}
