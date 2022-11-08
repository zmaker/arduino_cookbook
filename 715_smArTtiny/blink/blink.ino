// https://raw.githubusercontent.com/damellis/attiny/ide-1.6.x-boards-manager/package_damellis_attiny_index.json

void setup() {
  pinMode(0, OUTPUT);
}

void loop() {
  digitalWrite(0, !digitalRead(0));
  delay(500);
}
