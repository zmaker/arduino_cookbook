const byte RXD2 = 2;  //
const byte TXD2 = 3;  //

HardwareSerial hserial(1);

void setup() {
  Serial.begin(9600);
  hserial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
}

void loop() {
  if (hserial.available()) {
    char c = hserial.read();
    Serial.write(c);
    if (c == '1') {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
    hserial.write(c);
  }
}