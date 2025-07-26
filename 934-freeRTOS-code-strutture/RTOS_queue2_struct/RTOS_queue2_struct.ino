QueueHandle_t queue;

struct Messaggio {
  int id;
  char testo[32];
};

void TaskSender (void *parm){
  int count = 0;
  while(1) {
    Messaggio m;
    m.id = count++;
    snprintf(m.testo, sizeof(m.testo), "Msg n. %d", m.id);

    if (xQueueSend(queue, &m, pdMS_TO_TICKS(100)) == pdPASS) {
      Serial.println("msg tx");
    } else {
      Serial.println("msg err");
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void TaskReceiver (void *parm){
  Messaggio mr;
  while(1) {
    if (xQueueReceive(queue, &mr, pdMS_TO_TICKS(500)) == pdPASS) {
      Serial.print("id: ");
      Serial.print(mr.id);
      Serial.print(" txt: ");
      Serial.println(mr.testo);
    } else {
      //
    }

    vTaskDelay(pdMS_TO_TICKS(300));

  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("queue struttura");

  queue = xQueueCreate(5, sizeof(Messaggio));
  if (queue == NULL) {
    Serial.println("queue non creata");
    while(1);
  }

  xTaskCreatePinnedToCore(TaskSender, "sender", 2048, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(TaskReceiver, "receiver", 2048, NULL, 1, NULL, 1);
}

void loop() {
  
}
