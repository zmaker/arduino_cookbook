void setup() {
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case 'a':
        Serial.println("ON");
        break;
      case 's':
        Serial.println("OFF");
        break;
      case 'x':
        Serial.println("Accendi luce");
        break;
      case '\n':
      case '\r':
        Serial.println("-");
        break;
      default:
        Serial.println("???");
    }
  }
}
