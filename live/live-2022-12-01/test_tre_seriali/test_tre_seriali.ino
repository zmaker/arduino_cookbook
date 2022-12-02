#define TXD1 25
#define RXD1 26

#define TXD2 13
#define RXD2 12

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  Serial.println("\ntest seriali multiple - 3");
}

void loop() {
  while (true) {
    if (Serial.available()) {
      char ch = Serial.read();
      Serial1.write('-');
      Serial1.write(ch);
      if (ch == '2') {
        Serial.println("passo a Serial2");
        break;
      }
    }
    if (Serial1.available()) {
      char ch = Serial1.read();
      Serial.write('.');
      Serial.write(ch);
    }
  }

  while (true) {
    if (Serial.available()) {
      char ch = Serial.read();
      Serial2.write('#');
      Serial2.write(ch);
      if (ch == '1') {
        Serial.println("passo a Serial1");
        break;
      }
    }
    if (Serial2.available()) {
      char ch = Serial2.read();
      Serial.write('_');
      Serial.write(ch);
    }
  }

}
