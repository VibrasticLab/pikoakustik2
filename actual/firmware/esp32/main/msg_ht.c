/**
 * @file msg_ht.c
 * @brief STM32 message package code
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

extern uint8_t runIdle;

/**
 * @brief LED Task Loop
 *
 * @param pvParameter
 */
static void stm32statusTask(void *pvParameter){
  while (1) {
    vTaskDelay(100 / portTICK_PERIOD_MS);

    if(gpio_get_level(PIN_STMSTT_READY)==1)runIdle=HT_STATE_IDLE;
    else if(gpio_get_level(PIN_STMSTT_READY)==0)runIdle=HT_STATE_PREP;
  }
}

void msg_htiosttInit(void){
  gpio_config_t stm32iostt_conf;

  stm32iostt_conf.intr_type = GPIO_INTR_DISABLE;
  stm32iostt_conf.mode = GPIO_MODE_INPUT;
  stm32iostt_conf.pin_bit_mask = IO_STMSTT_IN;
  stm32iostt_conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
  stm32iostt_conf.pull_up_en = GPIO_PULLUP_DISABLE;
  gpio_config(&stm32iostt_conf);

  xTaskCreate(&stm32statusTask, "stm32status_task", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */
