void setup() {
 Serial.begin(9600); 
}

int soglia = 5;

void loop() {
  int v = analogRead(A0);

  if ( (v > 245 - soglia) && (v < 245 + soglia) ) {
    Serial.println("tasto1");
  } else if ( (v > 488 - soglia) && (v < 488 + soglia) ) {
    Serial.println("tasto2");
  } else if ( (v > 745 - soglia) && (v < 745 + soglia) ) {
    Serial.println("tasto3");
  }

  Serial.println(v);
}
