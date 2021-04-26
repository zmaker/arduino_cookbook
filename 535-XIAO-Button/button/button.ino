/**
 * Seeeduino XIAO - Button demo
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */

void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, INPUT);
}

void loop() {
  static byte stato;
  if (digitalRead(6)) {
    digitalWrite(7, stato);    
    stato = !stato;
    delay(300);
  }
}
