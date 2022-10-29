#include <Arduino_FreeRTOS.h>

void TaskLoop1(void *parms);
void TaskLoop2(void *parms);

void setup() {  
  xTaskCreate(TaskLoop1, "Loop1", 128, NULL, 2, NULL);
  xTaskCreate(TaskLoop2, "Loop2", 128, NULL, 1, NULL);
}

void loop() {}

void TaskLoop1(void *parms){
  pinMode(2, OUTPUT);
  
  while(true) {
    digitalWrite(2, HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);  
    digitalWrite(2, LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);  
  }
}

void TaskLoop2(void *parms){
  pinMode(3, OUTPUT);
  
  while(true) {
    digitalWrite(3, HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);  
    digitalWrite(3, LOW);
    vTaskDelay(300/portTICK_PERIOD_MS);  
  }  
}
