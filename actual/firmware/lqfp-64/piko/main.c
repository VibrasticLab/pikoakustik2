/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "ch.h"
#include "hal.h"

#include "shell.h"

#include "ht_config.h"

#include "ht_led.h"

extern uint8_t mode_led;

/**
 * @brief status to control LED thread start
 */
static uint8_t stt_readyAll = FALSE;

static THD_WORKING_AREA(waRunLed, 128);
#define ThdFunc_RunLED THD_FUNCTION

/**
 * @brief Thread for System Running Indicator
 * @details Smallest Thread to check either system in Run or Freeze
 */
static ThdFunc_RunLED(thdRunLed, arg) {
  (void)arg;
  chRegSetThreadName("run_led");

  while (true) {
    if(mode_led==LED_FAIL){
        palClearPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(50);
        palSetPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(100);
        palClearPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(50);
        palSetPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(1500);
    }
    else if(mode_led==LED_READY){
        palTogglePad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(500);
    }
    else if(mode_led==LED_CFILE){
        palSetPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(1);
    }
    else if(mode_led==LED_METRI){
        palTogglePad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(50);
    }
  }
}

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  palSetPadMode(GPIOA,LED_RUN,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA,LED_RUN);

#if USER_LED_BUTTON
  ht_led_Init();
  ht_led_Test();
//  ht_exti_Init();
#endif

  mode_led = LED_READY;

  while (true) {
      if(stt_readyAll==FALSE){
        chThdCreateStatic(waRunLed, sizeof(waRunLed),NORMALPRIO, thdRunLed, NULL);
        stt_readyAll = TRUE;
      }

      chThdSleepMilliseconds(1000);
  }
}
