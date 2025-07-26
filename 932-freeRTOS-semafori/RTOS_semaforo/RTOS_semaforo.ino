#include <Arduino.h>

bool task1Enabled = true;

SemaphoreHandle_t mutex;

void Task1 (void * parm){
  while(1){

    xSemaphoreTake(mutex, portMAX_DELAY);  
    bool enabled = task1Enabled;
    xSemaphoreGive(mutex);

    if (enabled) {
      Serial.print(".");
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void Task2 (void * parm){
  while(1){
    xSemaphoreTake(mutex, portMAX_DELAY);  
    task1Enabled = !task1Enabled;
    xSemaphoreGive(mutex);
    
    Serial.println( task1Enabled ? "task1 on" : "task1 off" );
    
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("mutex");

  mutex = xSemaphoreCreateMutex();
  if (mutex == NULL) {
    Serial.println("mutex non creato");
    while(1);
  }

  xTaskCreatePinnedToCore(Task1, "task1", 1000, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(Task2, "task2", 1000, NULL, 1, NULL, 1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
