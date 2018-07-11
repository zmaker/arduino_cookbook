/*
Riceve dati da processing
*/
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (Serial.available()) { // If data is available to read,
     int val = Serial.read(); // read it and store it in val
     if (val == '1') { 
       digitalWrite(13, HIGH); // turn the LED on
     } else {
       digitalWrite(13, LOW); // otherwise turn it off
     }
  }  
}
