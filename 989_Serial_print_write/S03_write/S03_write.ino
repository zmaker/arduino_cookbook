void setup() {
  Serial.begin(9600, SERIAL_8N1);

  Serial.write(65);
  Serial.print(65);
  
  uint8_t dati[] = {0x01, 0x02, 0x03, 0x0A};
  Serial.write(dati, sizeof(dati)); 
  uint8_t dati2[] = {0x41, 0x42, 0x43, 0x44};
  Serial.write(dati2, sizeof(dati2)); 
}

void loop() {
  // put your main code here, to run repeatedly:

}
