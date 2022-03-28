/**
 * @file    msg_my.c
 * @brief   ESP32 message package code.
 *
 * @addtogroup Console
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"

#include "shell.h"
#include "chprintf.h"

#include "ht_config.h"

#include "ht_console.h"
#include "ht_led.h"
#include "msg_my.h"

extern uint8_t mode_led;

void esp32_MsgStatus(BaseSequentialStream *chp, int argc, char *argv[]){
  (void) argv;

  uint8_t numState;

  if(argc == 0){
      switch (mode_led) {
        case LED_READY: numState = HT_STATE_IDLE; break;
        case LED_METRI: numState = HT_STATE_RUN; break;
        default: numState = HT_STATE_PREP;break;
      }
      chprintf(chp,"htstate %d\r\n",numState);
  }
}

void esp32_InfoStatus(uint8_t status){
  switch (status) {
    case HT_STATE_PREP: ht_commUART_Msg("htstate 0\r\n"); break;
    case HT_STATE_IDLE: ht_commUART_Msg("htstate 1\r\n"); break;
    case HT_STATE_RUN: ht_commUART_Msg("htstate 0\r\n"); break;
    default: break;
  }
}

/** @} */
