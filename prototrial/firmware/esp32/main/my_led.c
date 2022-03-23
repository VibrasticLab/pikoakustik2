/**
 * @file my_led.c
 * @brief LED source
 *
 * @addtogroup GPIO
 * @{
 */

#include "my_includes.h"

/**
 * @brief LED Blink task
 *
 * @param pvParameter
 */
static void ledTask(void *pvParameter){
    while (1) {
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);

        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
    }
}

/**
 * @brief LED start
 *
 */
void ledInit(void){
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&ledTask, "led_task", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */