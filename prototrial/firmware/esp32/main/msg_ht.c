/**
 * @file msg_ht.c
 * @brief STM32 message package code
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

extern uint8_t runIdle;

static void register_MsgStatus(void);

void registerSTM32Messages(void){
  register_MsgStatus();
}

/**
 * @brief Asking STM32 routine loop task
 * @param pvParameter
 */
static void askingSTM32Task(void *pvParameter){
    while (1) {
        if(runIdle==HT_STATE_PREP){
          printf("htstate\r\n");
        }
        vTaskDelay(BLINK_DELAY / portTICK_PERIOD_MS);
    }
}

/**
 * @brief Asking STM32 routine start
 */
void askingSTM32Init(void){
  xTaskCreate(&askingSTM32Task, "asking_task", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/**
 * @brief Response if STM32 sending info of current status
 * @param argc
 * @param argv
 * @return
 */
static int stm32_MsgStatus(int argc, char **argv){
  uint8_t num;

  /** argc always >=1 with argv[0] always command string */
  if(argc  > 1){
    num = atoi(argv[1]);

    switch (num) {
      case HT_STATE_PREP: runIdle = HT_STATE_PREP; break;
      case HT_STATE_IDLE: runIdle = HT_STATE_IDLE; break;
      case HT_STATE_RUN: runIdle = HT_STATE_RUN; break;
      default:
        break;
    }
  }

  return 0;
}

static void register_MsgStatus(void){
    const esp_console_cmd_t cmd = {
        .command = "htstate",
        .help = "STM32 Status Response command",
        .hint = NULL,
        .func = &stm32_MsgStatus,
    };
    esp_console_cmd_register(&cmd);
}

/** @} */
