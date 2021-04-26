/**
 * Seeeduino XIAO - Blink demo
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */

void setup() {
  pinMode(7, OUTPUT);

}

void loop() {
  static byte stato;
  digitalWrite(7, stato);
  stato = !stato;
  delay(500);
}
