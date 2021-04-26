/**
 * Seeeduino XIAO
 * Link per installare la scheda
 * https://files.seeedstudio.com/arduino/package_seeeduino_boards_index.json
 */

void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  //analogReadResolution(12);
  analogReadResolution(10);
}

void loop() {  
  int val = analogRead(5);
  Serial.println(val);
  //analogWrite(7, map(val, 1023, 0, 0, 255));
  delay(100);
}
