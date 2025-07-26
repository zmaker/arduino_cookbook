QueueHandle_t queue;

void TaskSender(void *parms){
  int count = 0;
  while(1) {
    if (xQueueSend(queue, &count, pdMS_TO_TICKS(100)) == pdPASS) {
      Serial.println("TX ok: "+String(count));
    } else {
      Serial.println("TX ko");
    }
    count++;
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskReceiver(void *parms){
  int dato;
  while(1) {
    if (xQueueReceive(queue, &dato, pdMS_TO_TICKS(300)) == pdPASS) {
      Serial.println("RX: "+String(dato));
    } else {
      //Serial.println("RX nulla");
    }
    vTaskDelay(pdMS_TO_TICKS(300));
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("queue");

  queue = xQueueCreate(5, sizeof(int));
  if (queue == NULL) {
    Serial.println("queue non creata");
    while(1);
  }

  xTaskCreatePinnedToCore(TaskSender, "sender", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskReceiver, "receiver", 2048, NULL, 1, NULL, 1);
}

void loop() {
  
}
