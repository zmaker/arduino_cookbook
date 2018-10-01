//blnk su 13

void setup() {
  //data direction
  DDRB = B00000000; 
  Serial.begin(9600);
}

void loop() {
  int n = PINB;
  if (n != 0) {
    Serial.println(n, BIN);
  }
}
