#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "hal/gpio_types.h"

#define LED_GPIO 2

void app_main(void) {
	
	//configuro il pin
	gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
	
    while (true) {
        printf("Hello from app_main!\n");
		
		gpio_set_level(LED_GPIO, 1);
        sleep(1);
		gpio_set_level(LED_GPIO, 0);
		sleep(2);
    }
}
