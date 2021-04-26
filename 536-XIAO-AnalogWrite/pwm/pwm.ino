/**
 * Seeeduino XIAO - Button demo
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
}

int val = 0;
int dir = 1;

void loop() {  
  val = val + dir;
  if (val >=  255) {
    dir = -1;
  }
  if (val <= 0) {
    dir = 1;
  }
  Serial.println(val);
  analogWrite(7, val);
  delay(10);
}
