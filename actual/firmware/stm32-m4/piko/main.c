/**
 * @file    main.c
 * @brief   Main Code
 *
 * @addtogroup GPIO
 * @{
 */

#include "ch.h"
#include "hal.h"

#include "shell.h"

#include "ht_config.h"

#include "ht_led.h"
#include "ht_mmc.h"
#include "ht_btn.h"
#include "ht_audio.h"
#include "ht_metri.h"
#include "ht_console.h"

#include "msg_my.h"

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
#if USER_LED_RUN
        palTogglePad(GPIOA, LED_RUN);
#else
        palSetPad(GPIOA, LED_RUN);
#endif
        chThdSleepMilliseconds(50);
    }
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

#if USER_ESP32
 #if USER_ESPIOSTT
  my_iosttInit();
 #endif
#endif

#if USER_LED
  ht_led_Init();
  ht_led_Test();
#endif

#if USER_BUTTON
  ht_btn_Init();
#endif

#if USER_SERIAL
  shellInit();

  #if USER_SER_USB
  ht_commUSB_Init();
  #endif

  #if USER_SER_UART
  ht_commUART_Init();
  #endif
#endif

#if USER_MMC
   ht_mmc_Init();
   ht_mmc_InitCheck();
#else
  mode_led=LED_READY;
#endif

#if USER_AUDIO
  ht_audio_Init();
 #if USER_AUDIO_TEST
  ht_audio_TestBoth();
 #endif
#endif

#if USER_METRI
  ht_metri_Init();
#endif

  if(mode_led==LED_READY){
#if USER_ESP32
 #if USER_ESPIOSTT
    my_iosttSTMready(TRUE);
 #endif
#endif
  }

  while (true) {

#if USER_SERIAL
  #if USER_SER_USB
    ht_commUSB_shInit();
  #endif

  #if USER_SER_UART
    ht_commUART_shInit();
  #endif
#endif

    if(stt_readyAll==FALSE){
      chThdCreateStatic(waRunLed, sizeof(waRunLed),NORMALPRIO, thdRunLed, NULL);
      stt_readyAll = TRUE;
    }

    chThdSleepMilliseconds(1000);
  }
}
