#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

TimerHandle_t timer1;

void onTimer(TimerHandle_t t) {
  Serial.println("Task RTOS");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  Serial.println("Task RTOS ");

  timer1 = xTimerCreate("t1", pdMS_TO_TICKS(5000), pdFALSE, NULL, onTimer);
  xTimerStart(timer1, 0);
  
}

void loop() {
}
