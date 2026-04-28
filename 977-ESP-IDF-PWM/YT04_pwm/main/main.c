#include "freertos/idf_additions.h"
#include "freertos/projdefs.h"
#include "hal/ledc_types.h"
#include "soc/clk_tree_defs.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <driver/ledc.h>
#include "esp_timer.h"

// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/peripherals/ledc.html

#define LED_GPIO 5

int64_t t1 = 0;
int64_t now = 0;
int pwm = 0;

void app_main(void) {
	
	//config timer pwm
	ledc_timer_config_t timer = {
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.duty_resolution = LEDC_TIMER_10_BIT,
		.timer_num = LEDC_TIMER_0,
		.freq_hz = 5000,
		.clk_cfg = LEDC_AUTO_CLK
	};
	ledc_timer_config(&timer);
	
	//canale
	ledc_channel_config_t channel = {
		.gpio_num = LED_GPIO,
		.speed_mode = LEDC_HIGH_SPEED_MODE,
		.channel = LEDC_CHANNEL_0,
		.timer_sel = LEDC_TIMER_0,
		.duty = 0,
		.hpoint = 0
	};
	ledc_channel_config(&channel);
	 
    while (true) {
		now = esp_timer_get_time() / 1000;
		if ((now - t1) > 50) {
			
			pwm += 10;
			if (pwm > 1023) pwm = 0;
			
			ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, pwm);
			ledc_update_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
			
			t1 = now;
		}
		vTaskDelay(pdMS_TO_TICKS(5));
    }
}
