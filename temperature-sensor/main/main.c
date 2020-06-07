/* adc example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_log.h"
#include <math.h>

static const char *TAG = "adc example";

static void adc_task() {
    uint16_t adc_data;
    double temp = 0;

    while (1) {
        if (ESP_OK == adc_read(&adc_data)) {      
            temp = (adc_data * (3.3 / 1024)) * 100;     
            ESP_LOGI(TAG, "adc read: %f\r\n", temp);
        }

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main()
{
    adc_config_t adc_config;

    adc_config.mode = ADC_READ_TOUT_MODE;
    adc_config.clk_div = 8;
    ESP_ERROR_CHECK(adc_init(&adc_config));

    xTaskCreate(adc_task, "adc_task", 1024, NULL, 5, NULL);
}
