void setup() {
  Serial.begin(9600);
  Serial.println("\n\nbit test");
  uint8_t n = 0;
  n = B11001110;
  prt(n);

  n = n << 1;
  prt(n);
  n = n << 1;
  prt(n);
  n = n << 1;
  prt(n);

  Serial.println("\nAND");
  n = B11001110;
  n = n & B00001111;
  prt(n);

  Serial.println("\nOR");
  n =     B11001110;
  n = n | B00001111;
  prt(n);

  Serial.println("\nNOT");
  n =     B11001110;
  n = ~n;
  prt(n);

  Serial.println("\nXOR");
  n =     B00001100;
  n = n ^ B00001010;
  prt(n);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void prt(uint8_t num){
  for (int i = 7; i >= 0; i--) {
    bool b = bitRead(num, i);
    Serial.print(b);    
  }
  Serial.print("\n"); 
}
