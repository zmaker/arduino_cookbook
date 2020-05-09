/*
  022 - Rilevamento ostacoli - avoidance
  https://win.adrirobot.it/sensori/37_in_1/KY-032-Obstacle-avoidance-sensor-module.htm
*/

void setup() {
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
}

void loop() {
  if (digitalRead(2)==LOW) {
    digitalWrite(13, HIGH);
  } else {
    digitalWrite(13, LOW);  
  }
}
