/**
 * @file msg_ht.c
 * @brief STM32 message package code
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

/**
 * @brief LED Task Loop
 *
 * @param pvParameter
 */
static void stm32statusTask(void *pvParameter){
  while (1) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void msg_htiosttInit(void){
  xTaskCreate(&stm32statusTask, "stm32status_task", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */
