/**
 * @file    ht_btn.c
 * @brief   Button routine code.
 *
 * @addtogroup GPIO
 * @{
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "ht_config.h"

#include "ht_led.h"
#include "ht_btn.h"
#include "ht_audio.h"
#include "ht_metri.h"
#include "ht_console.h"

extern uint8_t mode_status;
extern uint8_t mode_step;
extern uint8_t mode_led;
extern uint8_t numresp;

/**
 * @brief Mode button combination for entering next mode
 */
static uint8_t mode_btnA;

/**
 * @brief Mode button combination for entering next mode
 */
static uint8_t mode_btnB;

/**
 * @brief Mode button combination for entering next mode
 */
static uint8_t mode_btnC;

/**
 * @brief Reset Button function called by EXTI callback
 */
static void reset_ledbutton(void){
    mode_btnA=0;
    mode_btnB=0;
    mode_btnC=0;
    led_answer_off();
    led_result_off();
}

/**
 * @brief Callback function for entering Standby Mode
 */
static void exti_idle_cb(void){
    ht_commUSB_Msg("Entering Mode: Standby\r\n");
    mode_status=STT_STDBY;

    reset_ledbutton();

    led_resultYES();
}

/**
 * @brief Callback function for entering Check Save File Mode
 */
static void exti_stdby_cb(void){
    ht_commUSB_Msg("Entering Mode: Checking Save File\r\n");
    palSetPad(GPIOA, LED_RUN);

    mode_led=LED_CFILE;
    mode_status=STT_CFILE;

    reset_ledbutton();
}

/*******************************************/

/**
 * @brief Button answer A callback
 * @details Not called directly by any normal thread
 */
 static void btnA_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();

    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerA();
        mode_btnA=1;

        ht_commUSB_Msg("Entering Mode: Setup\r\n");
        mode_status = STT_SETUP;
    }
    else if(mode_status==STT_READY){
        if(mode_btnA==0){
            if((mode_btnB==1)||(mode_btnC==1)){
                exti_idle_cb();
                mode_btnA=1;
            }
        }
    }
    else if(mode_status==STT_STDBY){
        if(mode_btnA==0){exti_stdby_cb();}
    }
    else if(mode_status==STT_METRI){
        if(mode_step==STEP_WAIT){
            numresp = BTN_ANS_A;
            mode_step = STEP_CHK;
        }
    }

  chSysUnlockFromISR();
}

/**
 * @brief Button answer B callback
 * @details Not called directly by any normal thread
 */
 static void btnB_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();

    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerB();
        mode_btnB=1;

        ht_commUSB_Msg("Entering Mode: Setup\r\n");
        mode_status = STT_SETUP;
    }
    else if(mode_status==STT_READY){
        if(mode_btnB==0){
            if((mode_btnA==1)||(mode_btnC==1)){
                exti_idle_cb();
                mode_btnB=1;
            }
        }
    }
    else if(mode_status==STT_STDBY){
        if(mode_btnB==0){exti_stdby_cb();}
    }
    else if(mode_status==STT_METRI){
        if(mode_step==STEP_WAIT){
            numresp = BTN_ANS_B;
            mode_step = STEP_CHK;
        }
    }

  chSysUnlockFromISR();
}

/**
 * @brief Button answer C callback
 * @details Not called directly by any normal thread
 */
 static void btnC_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();

    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerC();
        mode_btnC=1;

        ht_commUSB_Msg("Entering Mode: Setup\r\n");
        mode_status = STT_SETUP;
    }
    else if(mode_status==STT_READY){
        if(mode_btnC==0){
            if((mode_btnA==1)||(mode_btnB==1)){
                exti_idle_cb();
                mode_btnC=1;
            }
        }
    }
    else if(mode_status==STT_STDBY){
        if(mode_btnC==0){exti_stdby_cb();}
    }
    else if(mode_status==STT_METRI){
        if(mode_step==STEP_WAIT){
            numresp = BTN_ANS_C;
            mode_step = STEP_CHK;
        }
    }

  chSysUnlockFromISR();
}

/*******************************************/

void ht_btn_Init(void){
	palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_PULLUP);
	palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_PULLUP);
	palSetPadMode(GPIOC, 2, PAL_MODE_INPUT_PULLUP);

	palEnableLineEvent(PAL_LINE(GPIOC, 0), PAL_EVENT_MODE_FALLING_EDGE);
	palSetLineCallback(PAL_LINE(GPIOC, 0), btnA_cb, NULL);

	palEnableLineEvent(PAL_LINE(GPIOC, 1), PAL_EVENT_MODE_FALLING_EDGE);
	palSetLineCallback(PAL_LINE(GPIOC, 1), btnB_cb, NULL);

	palEnableLineEvent(PAL_LINE(GPIOC, 2), PAL_EVENT_MODE_FALLING_EDGE);
	palSetLineCallback(PAL_LINE(GPIOC, 2), btnC_cb, NULL);

    mode_btnA=0;
    mode_btnB=0;
    mode_btnC=0;
}

/** @} */
