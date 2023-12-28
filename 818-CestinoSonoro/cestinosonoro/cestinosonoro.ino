#include <DFRobotDFPlayerMini.h>
#include <SoftwareSerial.h>

SoftwareSerial ss(3, 2); //RX, TX
DFRobotDFPlayerMini player;

void setup() {
  ss.begin(9600);
  Serial.begin(9600);

  Serial.println("cestino");
  if (!player.begin(ss)) {
    Serial.println("errore player");
    while(true);
  }
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);

  player.volume(30);
}

void loop() {
  if (digitalRead(4) == LOW) {
    digitalWrite(13, HIGH);
    player.play(4);
    delay(2000);
  } else {
    digitalWrite(13, LOW);
  }

}
