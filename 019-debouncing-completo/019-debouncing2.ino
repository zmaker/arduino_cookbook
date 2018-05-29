long t = 0;
long debounce_delay = 2000;

void setup() {
  pinMode(7, INPUT);
  Serial.begin(9600);
}

void loop() {
  if ( digitalRead(7) ){
    if ( (millis() - t) > debounce_delay) {
      Serial.println("ok");
      t = millis();  
    }     
  }
}
