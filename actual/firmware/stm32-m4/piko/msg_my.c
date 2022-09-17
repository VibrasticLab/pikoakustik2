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

#include "msg_my.h"

void my_iosttSTMready(uint8_t iostatus){
  if(iostatus==0)palClearPad(GPIOC, STATUS_RDY_PIN);
  else if(iostatus==1)palSetPad(GPIOC, STATUS_RDY_PIN);
}

void my_iosttSTMrun(uint8_t iostatus){
  if(iostatus==0)palClearPad(GPIOC, STATUS_RUN_PIN);
  else if(iostatus==1)palSetPad(GPIOC, STATUS_RUN_PIN);
}

void my_iosttInit(void){
  palSetPadMode(GPIOB, STATUS_IO_0, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, STATUS_IO_1, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB, STATUS_IO_2, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPad(GPIOB, STATUS_IO_1); // should always be high if connected to ESP32 IO-05
  palClearPad(GPIOB, STATUS_IO_2); // should always be low if connected to ESP32 IO-12

  palSetPadMode(GPIOC, STATUS_RDY_PIN, PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOC, STATUS_RUN_PIN, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOC, STATUS_RDY_PIN);
  palClearPad(GPIOC, STATUS_RUN_PIN);
}

/** @} */
