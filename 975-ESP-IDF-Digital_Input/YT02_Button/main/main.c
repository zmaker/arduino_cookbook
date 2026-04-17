#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "hal/gpio_types.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/gpio.html

#define BUTTON_GPIO 4

void app_main(void) {
	
	gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY);
	
    while (true) {
		
		int bt = !gpio_get_level(BUTTON_GPIO);
		if (bt == 1) {
			printf("BT premuto\n");	
		}
		        
		vTaskDelay(pdMS_TO_TICKS(50));
        //sleep(1);
    }
}
