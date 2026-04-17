#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void) {
	
	gpio_set_direction(5, GPIO_MODE_OUTPUT);
	
	uint32_t t1 = 0;
	int led = 0;
	
    while (true) {
		uint32_t now = pdTICKS_TO_MS(xTaskGetTickCount());
		if ((now - t1) > 500){
			led = !led;
			gpio_set_level(5, led);
			
			t1 = now;
		}	
		vTaskDelay(pdTICKS_TO_MS(10));
    }
}
