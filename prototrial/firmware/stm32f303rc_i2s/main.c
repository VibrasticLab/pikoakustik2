/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#define LED_RUN     1 //PA.1

#define AUDIO_IO    GPIOC
#define AUDIO_L     9
#define AUDIO_R     8

#define I2S_BUFF_SIZE   512
#define TOTAL_BUFF_SIZE I2S_BUFF_SIZE*16

#define WEIRD_SINE  		FALSE
#define DEFAULT_ATTEN 		0.01
#define DEFAULT_AMPL_THD 	1

#define TEST_DURATION   20 // 200 ms each tone

static uint8_t stt_inPlay = FALSE;
static uint16_t sineSize = 0;
static int16_t i2s_tx_buf[TOTAL_BUFF_SIZE];
static I2SConfig i2scfg = {
    i2s_tx_buf,
    NULL,
    I2S_BUFF_SIZE,
    NULL,
    0,
    16,
};

static void ht_audio_Zero(void){
    uint16_t i;
    for(i=0;i<TOTAL_BUFF_SIZE;i++){
        i2s_tx_buf[i] = 0;
    }
}

static void ht_audio_Tone(double freq, double ampl){
    uint16_t i;
    uint16_t buffsize;
    double ysin;

    buffsize = (uint16_t) I2S_BUFF_SIZE/freq;

    // checking lowest possible amplitude
    double ampl_act;
    ampl_act = DEFAULT_ATTEN*ampl*32767;
    if(ampl_act<=DEFAULT_AMPL_THD){ampl = 0;}

    ht_audio_Zero();

    for(i=0;i<buffsize;i++){
        ysin = DEFAULT_ATTEN*ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));

#if WEIRD_SINE
        if(ysin >= 0){
            i2s_tx_buf[i]=ysin;
 #if USE_STEREO_ARRAY
            i2s_tx_buf[i+1]=ysin;
 #endif
        }
        if(ysin < 0){
            i2s_tx_buf[i]=ysin+65535;
 #if USE_STEREO_ARRAY
            i2s_tx_buf[i+1]=ysin+65535;
 #endif
        }
#else
        i2s_tx_buf[i] = ysin;
#endif
    }

    i2scfg.size = buffsize;
    sineSize = buffsize;
}

static void ht_audio_Play(uint16_t duration){
    if(stt_inPlay==TRUE){return;}
    else{stt_inPlay=TRUE;}

    i2sStartExchange(&I2SD2);

    chThdSleepMilliseconds(duration*10);

    ht_audio_Zero();
    i2sStopExchange(&I2SD2);

    stt_inPlay=FALSE;
}

static void ht_audio_DisableCh(void){
    palClearPad(AUDIO_IO,AUDIO_L);
    palClearPad(AUDIO_IO,AUDIO_R);
}

static void ht_audio_LeftCh(void){
    ht_audio_DisableCh();
    palSetPad(AUDIO_IO,AUDIO_L);
}

static void ht_audio_RightCh(void){
    ht_audio_DisableCh();
    palSetPad(AUDIO_IO,AUDIO_R);
}

static void ht_audio_TestTone(void){
    ht_audio_Tone(2.5,1);
}

static void ht_audio_TestBoth(void){
    chThdSleepMilliseconds(200);
    ht_audio_LeftCh();
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    chThdSleepMilliseconds(200);
    ht_audio_RightCh();
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    chThdSleepMilliseconds(200);
    ht_audio_LeftCh();
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    chThdSleepMilliseconds(200);
    ht_audio_RightCh();
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    ht_audio_DisableCh();
}

static void ht_audio_Init(void){
    i2sStart(&I2SD2, &i2scfg);
    ht_audio_Zero();

    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5));

    palSetPadMode(GPIOB, 10, PAL_MODE_RESET);
    palSetPadMode(GPIOC, 3 , PAL_MODE_RESET);

    palSetPadMode(AUDIO_IO,AUDIO_L,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(AUDIO_IO,AUDIO_R,PAL_MODE_OUTPUT_PUSHPULL);

    palClearPad(AUDIO_IO,AUDIO_L);
    palClearPad(AUDIO_IO,AUDIO_R);

    ht_audio_DisableCh();
}

THD_WORKING_AREA(waBlink, 128);
THD_FUNCTION(Blink, arg) {

  (void)arg;

  chRegSetThreadName("blinker 1");
  while (true) {
    palTogglePad(GPIOA, LED_RUN);
    chThdSleepMilliseconds(500);
  }
}

/****************************** EXTI Test ************/

/* LED Answer ON */
#define led_answerA() palClearPad(GPIOA,4)
#define led_answerB() palClearPad(GPIOB,0)
#define led_answerC() palClearPad(GPIOB,1)

static void led_answer_off(void){
    palSetPad(GPIOA,4);
    palSetPad(GPIOB,0);
    palSetPad(GPIOB,1);
}

static void btnA_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();
  led_answer_off();
  led_answerA();
  chSysUnlockFromISR();
}

static void btnB_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();
  led_answer_off();
  led_answerB();
  chSysUnlockFromISR();
}

static void btnC_cb(void *arg) {

  (void)arg;

  chSysLockFromISR();
  led_answer_off();
  led_answerC();
  chSysUnlockFromISR();
}

/*****************************************************/

int main(void) {

  halInit();
  chSysInit();

  palSetPadMode(GPIOA,LED_RUN,PAL_MODE_OUTPUT_PUSHPULL);
  palClearPad(GPIOA,LED_RUN);

  palSetPadMode(GPIOA,4,PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB,0,PAL_MODE_OUTPUT_PUSHPULL);
  palSetPadMode(GPIOB,1,PAL_MODE_OUTPUT_PUSHPULL);

  ht_audio_Init();
  ht_audio_TestBoth();

  palSetPadMode(GPIOC, 0, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOC, 1, PAL_MODE_INPUT_PULLUP);
  palSetPadMode(GPIOC, 2, PAL_MODE_INPUT_PULLUP);

  palEnableLineEvent(PAL_LINE(GPIOC, 0), PAL_EVENT_MODE_FALLING_EDGE);
  palSetLineCallback(PAL_LINE(GPIOC, 0), btnA_cb, NULL);

  palEnableLineEvent(PAL_LINE(GPIOC, 1), PAL_EVENT_MODE_FALLING_EDGE);
  palSetLineCallback(PAL_LINE(GPIOC, 1), btnB_cb, NULL);

  palEnableLineEvent(PAL_LINE(GPIOC, 2), PAL_EVENT_MODE_FALLING_EDGE);
  palSetLineCallback(PAL_LINE(GPIOC, 2), btnC_cb, NULL);

  chThdCreateStatic(waBlink, sizeof(waBlink), NORMALPRIO, Blink, NULL);

  while (true) {
    chThdSleepMilliseconds(500);
  }
}
