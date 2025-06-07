uint64_t tm1;
bool FIRED = false;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Task Software ");
  tm1 = millis();
}

void loop() {
  
  if (((millis() - tm1) > 5000) && !FIRED ) {
    Serial.println("Timer scattato!");
    FIRED = true;
  }

}
