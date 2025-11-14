HardwareSerial qrreader(2); //UART2

void setup() {
  Serial.begin(115200);
  qrreader.begin(9600, SERIAL_8N1, 16, 17); //RX=16 e TX=17

  Serial.println("Attendo il codice");
}

void loop() {
  if (qrreader.available()) {
    String dati = qrreader.readStringUntil('\n');
    Serial.println(dati);
  }

}
