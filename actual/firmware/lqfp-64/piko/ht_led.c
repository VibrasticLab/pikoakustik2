/**
 * @file    ht_led.c
 * @brief   LED Indicator code.
 *
 * @addtogroup GPIO
 * @{
 */

#include <stdint.h>

#include "ch.h"
#include "hal.h"

#include "ht_led.h"

/**
 * @brief LED Mode global variable
 */
uint8_t mode_led=LED_FAIL;

void led_answer_off(void){
    palSetPad(GPIOA,LED_ANSA);
    palSetPad(GPIOB,LED_ANSB);
    palSetPad(GPIOB,LED_ANSC);
}

void led_result_off(void){
    palSetPad(GPIOA,LED_TRUE);
    palSetPad(GPIOA,LED_FALSE);
}

void ht_led_Init(void){
    palSetPadMode(GPIOA,LED_TRUE,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOA,LED_FALSE,PAL_MODE_OUTPUT_PUSHPULL);

    palSetPadMode(GPIOA,LED_ANSA,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,LED_ANSB,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOB,LED_ANSC,PAL_MODE_OUTPUT_PUSHPULL);

    led_answer_off();
    led_result_off();
}

void ht_led_Test(void){
    led_answer_off();
    led_result_off();
    chThdSleepMilliseconds(LED_TEST);

    palClearPad(GPIOA,LED_FALSE);
    chThdSleepMilliseconds(LED_TEST);
    led_result_off();

    palClearPad(GPIOA,LED_TRUE);
    chThdSleepMilliseconds(LED_TEST);
    led_result_off();

    palClearPad(GPIOA,LED_ANSA);
    chThdSleepMilliseconds(LED_TEST);
    led_answer_off();

    palClearPad(GPIOB,LED_ANSB);
    chThdSleepMilliseconds(LED_TEST);
    led_answer_off();

    palClearPad(GPIOB,LED_ANSC);
    chThdSleepMilliseconds(LED_TEST);
    led_answer_off();
}

/** @} */
