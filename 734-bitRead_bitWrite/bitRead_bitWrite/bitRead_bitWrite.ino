void setup() {
  Serial.begin(9600);

  uint8_t n, t = 0;
  n = B11001110;

  Serial.println("\nlettura numero:");
  for (int i = 7; i >= 0; i--) {
    bool b = bitRead(n, i);
    Serial.print(b);
  }
  Serial.print("\n");

  bitWrite(n, 0, 1);
  prt(n);

  bitWrite(n, 1, 0);
  prt(n);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void prt(uint8_t n){
  for (int i = 7; i >= 0; i--) {
    bool b = bitRead(n, i);
    Serial.print(b);
  }
  Serial.print("\n");
}
