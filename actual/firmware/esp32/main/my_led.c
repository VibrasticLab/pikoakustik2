/**
 * @file my_led.c
 * @brief LED source
 *
 * @addtogroup GPIO
 * @{
 */

#include "my_includes.h"

uint16_t led_delay = 500;

/**
 * @brief LED Task Loop
 *
 * @param pvParameter
 */
static void ledTask(void *pvParameter){
    while (1) {
        gpio_set_level(MY_LED_GPIO, 0);
        vTaskDelay(led_delay / portTICK_PERIOD_MS);

        gpio_set_level(MY_LED_GPIO, 1);
        vTaskDelay(led_delay / portTICK_PERIOD_MS);
    }
}

void my_ledInit(void){
    gpio_reset_pin(MY_LED_GPIO);
    gpio_set_direction(MY_LED_GPIO, GPIO_MODE_OUTPUT);

    xTaskCreate(&ledTask, "led_task", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

void my_ledDisabled(void){
    gpio_reset_pin(MY_LED_GPIO);
    gpio_set_direction(MY_LED_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(MY_LED_GPIO, 1);
}

/** @} */
