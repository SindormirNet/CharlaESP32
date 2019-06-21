#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "esp_log.h"

static const char* TAG = "sindormir.net - test logs";

#define BLINK_GPIO CONFIG_BLINK_GPIO

void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);

    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while(1) {
        gpio_set_level(BLINK_GPIO, 0);
	ESP_LOGI(TAG, "[LED] On\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(BLINK_GPIO, 1);
	ESP_LOGE(TAG, "[LED] Off\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    printf("Esta es una cosa que puedo hacer aquí: %d, %f\n", 12, 5.283333);
    ESP_LOGW(TAG, "Inicializando\n");
    xTaskCreate(&blink_task, "blink_task", 10000, NULL, 5, NULL);
}
