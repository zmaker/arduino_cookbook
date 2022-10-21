TaskHandle_t th1, th2;

void setup() {
  Serial.begin(115200);

  xTaskCreatePinnedToCore(
    Loop1, "Loop1", 10000, NULL, 1, &th1, 0
  );
  delay(500);
  xTaskCreatePinnedToCore(
    Loop2, "Loop2", 10000, NULL, 1, &th2, 1
  );
}

void loop() {  
}

void Loop1(void * parms){
  Serial.print("core: ");
  Serial.println(xPortGetCoreID());

  while(true) {
    Serial.println("hello");
    delay(1000);
  }
}

void Loop2(void * parms){
  Serial.print("core: ");
  Serial.println(xPortGetCoreID());

  while(true) {
    Serial.println("ciao!");
    delay(650);
  }

}