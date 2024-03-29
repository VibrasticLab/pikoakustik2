/**
 * @file    ht_audio.c
 * @brief   Audio Generator code.
 *
 * @addtogroup Audio
 * @{
 */

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "ch.h"
#include "hal.h"

#include "ht_audio.h"

/**
 * @brief State if DAC still playing a tone
 */
uint8_t stt_inPlay = FALSE;

/**
 * @brief Sine Array size.
 * @details Should be same size as i2scfg.size
 */
uint16_t sineSize = 0;

/**
 * @brief I2S Transmit buffer
 */
int16_t i2s_tx_buf[I2S_BUFF_SIZE];

/**
 * @brief I2S Protocol config struct
 */
static I2SConfig i2scfg = {
    i2s_tx_buf,
    NULL,
    I2S_BUFF_SIZE,
    NULL,
    0,
    16,
};

void ht_audio_Init(void){
    i2sStart(&I2SD2, &i2scfg);
    ht_audio_Zero();

/* NOTES:
 * I2S2 on F401RE can also using F303RC's I2S2 pins
 */
#ifdef PCB_P3
    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5));

    palSetPadMode(GPIOB,AUDIO_LR,PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOB,AUDIO_LR);
#endif

#ifdef PCB_P2
  #ifdef ST_F303RC
    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5));

    palSetPadMode(GPIOB, 10, PAL_MODE_RESET);
    palSetPadMode(GPIOC, 3 , PAL_MODE_RESET);
  #endif

  #ifdef ST_F401RE
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOC, 3 , PAL_MODE_ALTERNATE(5));
  #endif

    palSetPadMode(GPIOC,AUDIO_L,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(GPIOC,AUDIO_R,PAL_MODE_OUTPUT_PUSHPULL);

    palClearPad(GPIOC,AUDIO_L);
    palClearPad(GPIOC,AUDIO_R);
#endif

    ht_audio_DisableCh();
}

void ht_audio_Zero(void){
    uint16_t i;
    for(i=0;i<I2S_BUFF_SIZE;i++){
        i2s_tx_buf[i] = 0;
    }
}

void ht_audio_Tone(double freq, double ampl){
    uint16_t i;
    uint16_t buffsize;
    double ysin;

    buffsize = (uint16_t) I2S_BUFF_SIZE/(FREQ_SCALE*freq);

    // checking lowest possible amplitude
    double ampl_act;
    ampl_act = DEFAULT_ATTEN*ampl*32767;
    if(ampl_act<=DEFAULT_AMPL_THD){ampl = 0;}

    ht_audio_Zero();

#if USE_STEREO_ARRAY
    for(i=0;i<buffsize;i=i+2){
        ysin = DEFAULT_ATTEN*ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));
        i2s_tx_buf[i] = ysin;
        i2s_tx_buf[i+1] = ysin;
    }
#else
    for(i=0;i<buffsize;i++){
        ysin = DEFAULT_ATTEN*ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));
        i2s_tx_buf[i] = ysin;
    }
#endif

    i2scfg.size = buffsize;
    sineSize = buffsize;
}

void ht_audio_ToneNoAtt(double freq, double ampl){
    uint16_t i;
    uint16_t buffsize;
    double ysin;

    buffsize = (uint16_t) I2S_BUFF_SIZE/(FREQ_SCALE*freq);

    // checking lowest possible amplitude
    double ampl_act;
    ampl_act = ampl*32767;
    if(ampl_act<=DEFAULT_AMPL_THD){ampl = 0;}

    ht_audio_Zero();

#if USE_STEREO_ARRAY
    for(i=0;i<buffsize;i=i+2){
        ysin = ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));
        i2s_tx_buf[i] = ysin;
        i2s_tx_buf[i+1] = ysin;
    }
#else
    for(i=0;i<buffsize;i++){
        ysin = ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));
        i2s_tx_buf[i] = ysin;
    }
#endif

    i2scfg.size = buffsize;
    sineSize = buffsize;
}

void ht_audio_ToneScale(double freq, double scale){
    double ampl_scale;

    if(scale>0 && scale<=11){
        ampl_scale = 2 / pow(2,12-scale);
        ht_audio_Tone(freq,ampl_scale);
    }
}

void ht_audio_ToneScaleNoAtt(double freq, double scale){
    double ampl_scale;

    if(scale>0 && scale<=11){
        ampl_scale = 2 / pow(2,12-scale);
        ht_audio_ToneNoAtt(freq,ampl_scale);
    }
}

void ht_audio_Play(uint16_t duration){
    if(stt_inPlay==TRUE){return;}
    else{stt_inPlay=TRUE;}

    i2sStartExchange(&I2SD2);

    chThdSleepMilliseconds(duration*10);

    ht_audio_Zero();
    i2sStopExchange(&I2SD2);

    stt_inPlay=FALSE;
}

void ht_audio_DisableCh(void){
#ifdef PCB_P2
    palClearPad(GPIOC,AUDIO_L);
    palClearPad(GPIOC,AUDIO_R);
#endif
}

void ht_audio_LeftCh(void){
#ifdef PCB_P3
    palClearPad(GPIOB,AUDIO_LR);
#endif
#ifdef PCB_P2
    ht_audio_DisableCh();
    palSetPad(GPIOC,AUDIO_L);
#endif
}

void ht_audio_RightCh(void){
#ifdef PCB_P3
    palSetPad(GPIOB,AUDIO_LR);
#endif
#ifdef PCB_P2
    ht_audio_DisableCh();
    palSetPad(GPIOC,AUDIO_R);
#endif
}

void ht_audio_TestTone(void){
    ht_audio_Tone(1.25,1);
}

void ht_audio_TestBoth(void){
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
#ifdef PCB_P3
    ht_audio_LeftCh();
#endif
}

void ht_audio_TestLeft(void){
    ht_audio_LeftCh();

    chThdSleepMilliseconds(200);
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    chThdSleepMilliseconds(200);
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    ht_audio_DisableCh();
#ifdef PCB_P3
    ht_audio_LeftCh();
#endif
}

void ht_audio_TestRight(void){
    ht_audio_RightCh();

    chThdSleepMilliseconds(200);
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    chThdSleepMilliseconds(200);
    ht_audio_TestTone();
    ht_audio_Play(TEST_DURATION);

    ht_audio_DisableCh();
#ifdef PCB_P3
    ht_audio_LeftCh();
#endif
}

/** @} */
