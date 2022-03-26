/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

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

#include "ht_includes.h"

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
  chRegSetThreadName("run led");

  while (true) {

#if USER_TEST_STATE
    if(mode_led==LED_FAIL){
        led_result_off();

        palClearPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(200);

        palSetPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(200);

        palClearPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(200);

        palSetPad(GPIOA, LED_RUN);
        chThdSleepMilliseconds(200);

 #if USER_LED_BUTTON
        led_result_off();
        led_resultYES();
        chThdSleepMilliseconds(200);

        led_result_off();
        led_resultNO();
        chThdSleepMilliseconds(200);
 #else
        chThdSleepMilliseconds(400);
 #endif
    }
    else if(mode_led==LED_READY){
        palTogglePad(GPIOA, LED_RUN);

 #if USER_LED_BUTTON
        led_result_off();
        led_resultYES();
        chThdSleepMilliseconds(200);

        led_result_off();
        led_resultNO();
        chThdSleepMilliseconds(200);
 #else
        chThdSleepMilliseconds(400);
 #endif
    }
#else
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
#endif

  }
}

/**
 * @brief Main Function as start entry
 * @return Nothing
 */
int main(void) {

  halInit();
  chSysInit();

  palSetPadMode(GPIOA,LED_RUN,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA,LED_RUN);

  mode_led = LED_READY;

#if USER_LED_BUTTON
  ht_led_Init();
  ht_led_Test();
#endif

  /*
   * Creates the blinker thread.
   */
  chThdCreateStatic(waRunLed, sizeof(waRunLed), NORMALPRIO, thdRunLed, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
}
