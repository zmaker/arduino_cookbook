void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(1);
  }

  int n = 100;
  int *p;

  p = &n;

  Serial.print("valore puntato da p: ");Serial.println(*p);
  *p = 99;
  Serial.print("valore puntato da p: ");Serial.println(*p);

  Serial.print("indirizzo di p: ");Serial.println((unsigned int)p, HEX);

}

void loop() {
  // put your main code here, to run repeatedly:

}
