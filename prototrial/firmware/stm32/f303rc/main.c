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

/*
 * Blinker thread #1.
 */
static THD_WORKING_AREA(waBlinker, 128);
static THD_FUNCTION(ThBlinker, arg) {

  (void)arg;

  chRegSetThreadName("blinker");
  while (true) {
    palSetPad(GPIOA, 1);
    chThdSleepMilliseconds(250);
    palClearPad(GPIOA, 1);
    chThdSleepMilliseconds(250);
  }
}

/**
 * @brief I2S Transmit buffer
 */
static uint16_t i2s_tx_buf[512*16];

/**
 * @brief I2S Protocol config struct
 */
static I2SConfig i2scfg = {
  i2s_tx_buf,
  NULL,
  512,
  NULL,
  0,
  16,
};

static void ht_audio_Init(void){
    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5));
}

static void ht_audio_Play(uint16_t duration){

    i2sStart(&I2SD2, &i2scfg);
    i2sStartExchange(&I2SD2);

    chThdSleepMilliseconds(duration*10);

    i2sStopExchange(&I2SD2);
    i2sStop(&I2SD2);
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

  palSetPadMode(GPIOA,1, PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA, 1);

  ht_audio_Init();
  ht_audio_Play(500);

  /*
   * Creates the example threads.
   */
  chThdCreateStatic(waBlinker, sizeof(waBlinker), NORMALPRIO+1, ThBlinker, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state, when the button is
   * pressed the test procedure is launched.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
