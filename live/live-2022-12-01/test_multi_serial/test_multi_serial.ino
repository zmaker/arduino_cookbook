#define TXD2 13
#define RXD2 12

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  Serial.println("test seriali multiple");
}

void loop() {
  if (Serial.available()) {
    char ch = Serial.read();
    Serial2.write('-');
    Serial2.write(ch);
  }
  if (Serial2.available()) {
    char ch = Serial2.read();
    Serial.write('.');
    Serial.write(ch);
  }

}
