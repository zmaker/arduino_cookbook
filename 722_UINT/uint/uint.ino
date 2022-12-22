void setup() {
  Serial.begin(9600);
  uint8_t n = 0;
  //0xFF;
  //B10101100
  n = 0xFF;
  Serial.print("n=");Serial.println(n);
  n++;
  Serial.print("n=");Serial.println(n);

  uint16_t m = 0;
  unsigned int i = 0;
  Serial.print("\nm=");Serial.println(m);
  Serial.print("i=");Serial.println(i);
  m = 0xFFFF;
  i = 0xFFFF;
  Serial.print("\nm=");Serial.println(m);
  Serial.print("i=");Serial.println(i);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
