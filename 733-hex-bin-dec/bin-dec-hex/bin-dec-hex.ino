void setup() {
  Serial.begin(9600);

  uint8_t n = 123;

  //come lo scrivo in binario?
  //lo tratto come binario!
  Serial.println("\n123 binario: ");    
  for (int i = 7; i >= 0; i--) {
    bool b = bitRead(n, i);
    Serial.print(b);    
  }

  Serial.println("\nhex: ");    
  Serial.println(n, HEX);    

  
  

}

void loop() {
  // put your main code here, to run repeatedly:

}
