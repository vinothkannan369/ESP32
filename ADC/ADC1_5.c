#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"



static esp_adc_cal_characteristics_t adc1_chars;

int adc_raw;


void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_12Bit, 0, &adc1_chars);
    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_12Bit));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11));

	while(1)  {
		vTaskDelay(100 / portTICK_RATE_MS);
		adc_raw = adc1_get_raw(ADC1_CHANNEL_5);
		printf("RAW ADC  = %d\n",adc_raw);

	}


}
