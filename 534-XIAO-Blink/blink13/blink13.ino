/**
 * Seeeduino XIAO - Blink demo
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 * 
 * pagina prodotto
 * https://wiki.seeedstudio.com/Seeeduino-XIAO/#analog-input-and-output
 */

void setup() {
  pinMode(13, OUTPUT);

}

void loop() {
  static byte stato;
  digitalWrite(13, stato);
  stato = !stato;
  delay(500);
}
