#include "esp_timer.h"

void timerCode(void* args) {
  Serial.println("Timer esp32 scattato!");
}

static esp_timer_handle_t timer;
const esp_timer_create_args_t timer_args = {
  .callback = &timerCode,
  .name = "timer1"
};

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Task ESP32 ");
  
  esp_timer_create(&timer_args, &timer);
  esp_timer_start_once(timer, 5000000);
  //esp_timer_start_periodic(timer, 2000000);
}

void loop() {
}
