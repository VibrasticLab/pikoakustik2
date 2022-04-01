/**
 * @file    ht_exti.c
 * @brief   External Interrupt code.
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
#include "ht_exti.h"
#include "ht_audio.h"
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

#if USER_TEST_MODE
/**
 * @brief Test button status variable
 */
static uint8_t test_button = 0;
#endif

#if !(USER_TEST_MODE)
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
 * @brief EXTI callback function for entering Standby Mode
 */
static void exti_idle_cb(void){
    ht_comm_Msg("Entering Mode: Standby\r\n");
    mode_status=STT_STDBY;

    reset_ledbutton();

    led_resultYES();
}

/**
 * @brief EXTI callback function for entering Check Save File Mode
 */
static void exti_stdby_cb(void){
    ht_comm_Msg("Entering Mode: Checking Save File\r\n");
    palSetPad(GPIOA, LED_RUN);

    mode_led=LED_CFILE;
    mode_status=STT_CFILE;

    reset_ledbutton();
}
#endif

/*******************************************/

/**
 * @brief Button answer A callback
 * @details Enumerated and not called directly by any normal thread
 */
static void extiAnsA(EXTDriver *extp, expchannel_t channel) {
    (void)extp;
    (void)channel;

#if USER_TEST_MODE
    if(test_button==0){
        led_answer_off();
        led_answerA();
        test_button = BTN_ANS_A;
    }
#else
    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerA();
        mode_btnA=1;

        ht_comm_Msg("Entering Mode: Setup\r\n");
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
#endif

    return;
}

/**
 * @brief Button answer B callback
 * @details Enumerated and not called directly by any normal thread
 */
static void extiAnsB(EXTDriver *extp, expchannel_t channel) {
    (void)extp;
    (void)channel;

#if USER_TEST_MODE
    if(test_button==0){
        led_answer_off();
        led_answerB();
        test_button = BTN_ANS_B;
    }
#else
    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerB();
        mode_btnB=1;

        ht_comm_Msg("Entering Mode: Setup\r\n");
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
#endif

    return;
}

/**
 * @brief Button answer C callback
 * @details Enumerated and not called directly by any normal thread
 */
static void extiAnsC(EXTDriver *extp, expchannel_t channel) {
    (void)extp;
    (void)channel;

#if USER_TEST_MODE
    if(test_button==0){
        led_answer_off();
        led_answerC();
        test_button = BTN_ANS_C;
    }
#else
    if(mode_status==STT_IDLE){
        led_answer_off();
        led_answerC();
        mode_btnC=1;

        ht_comm_Msg("Entering Mode: Setup\r\n");
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
#endif

    return;
}

/*******************************************/

/**
 * @brief External Interrupt Channel Config
 */
static const EXTConfig extcfg = {
  {
    {EXT_CH_MODE_FALLING_EDGE  | EXT_MODE_GPIOC, extiAnsA}, //0
    {EXT_CH_MODE_FALLING_EDGE  | EXT_MODE_GPIOC, extiAnsB}, //1
    {EXT_CH_MODE_FALLING_EDGE  | EXT_MODE_GPIOC, extiAnsC}, //2
    {EXT_CH_MODE_DISABLED, NULL}, //3
    {EXT_CH_MODE_DISABLED, NULL}, //4
    {EXT_CH_MODE_DISABLED, NULL}, //5
    {EXT_CH_MODE_DISABLED, NULL}, //6
    {EXT_CH_MODE_DISABLED, NULL}, //7
    {EXT_CH_MODE_DISABLED, NULL}, //8
    {EXT_CH_MODE_DISABLED, NULL}, //9
    {EXT_CH_MODE_DISABLED, NULL}, //10
    {EXT_CH_MODE_DISABLED, NULL}, //11
    {EXT_CH_MODE_DISABLED, NULL}, //12
    {EXT_CH_MODE_DISABLED, NULL}, //13
    {EXT_CH_MODE_DISABLED, NULL}, //14
    {EXT_CH_MODE_DISABLED, NULL}, //15
    {EXT_CH_MODE_DISABLED, NULL}, //16
    {EXT_CH_MODE_DISABLED, NULL}, //17
    {EXT_CH_MODE_DISABLED, NULL}, //18
    {EXT_CH_MODE_DISABLED, NULL}, //19
    {EXT_CH_MODE_DISABLED, NULL}, //20
    {EXT_CH_MODE_DISABLED, NULL}, //21
    {EXT_CH_MODE_DISABLED, NULL}  //22
  }
};

#if USER_TEST_MODE
static THD_WORKING_AREA(waAudioTest, 512);
#define ThdFunc_AudioTest THD_FUNCTION

/**
 * @brief Thread for Test Audio on Button command
 */
static ThdFunc_AudioTest(thdAudioTest, arg) {
    (void)arg;
    chRegSetThreadName("exti audio test");

    while(1){
        switch(test_button){
            case BTN_ANS_A:
                ht_commUSB_Msg("Testing Left Channel\r\n");
                ht_audio_TestLeft();
                break;
            case BTN_ANS_B:
                ht_commUSB_Msg("Testing Both Channel\r\n");
                ht_audio_TestBoth();
                break;
            case BTN_ANS_C:
                ht_commUSB_Msg("Testing Right Channel\r\n");
                ht_audio_TestRight();
                break;
            default: break;
        }

        test_button = 0;
        led_answer_off();
        chThdSleepMilliseconds(200);
    }
}
#endif

void ht_exti_Init(void){
    palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_PULLUP);
    palSetPadMode(GPIOC, 2, PAL_MODE_INPUT_PULLUP);

    extStart(&EXTD1, &extcfg);
    extChannelEnable(&EXTD1, 0);
    extChannelEnable(&EXTD1, 1);
    extChannelEnable(&EXTD1, 2);

    mode_btnA=0;
    mode_btnB=0;
    mode_btnC=0;

#if USER_TEST_MODE
    chThdCreateStatic(waAudioTest, sizeof(waAudioTest), NORMALPRIO, thdAudioTest, NULL);
#endif
}

/** @} */
