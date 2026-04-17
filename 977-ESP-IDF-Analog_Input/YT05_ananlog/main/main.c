#include "hal/adc_types.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <esp_adc/adc_oneshot.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "esp_log.h"

#define ADC_CHANNEL ADC_CHANNEL_6

void app_main(void) {
	
	adc_oneshot_unit_handle_t adc_handle;
	
	//init adc1
	adc_oneshot_unit_init_cfg_t init_cfg = {
		.unit_id = ADC_UNIT_1
	};
	adc_oneshot_new_unit(&init_cfg,  &adc_handle);
	
	//canale
	adc_oneshot_chan_cfg_t ch_conf =  {
		.bitwidth = ADC_BITWIDTH_DEFAULT,
		.atten = ADC_ATTEN_DB_12
	};
	adc_oneshot_config_channel(adc_handle, ADC_CHANNEL, &ch_conf);
	
    while (true) {
        int val = 0;
		adc_oneshot_read(adc_handle, ADC_CHANNEL, &val);
		printf("lettura: %d\n", val);
		vTaskDelay(pdMS_TO_TICKS(500));
    }
}
