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
int16_t i2s_tx_buf[TOTAL_BUFF_SIZE];

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

    palSetPadMode(GPIOB, 12, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOB, 10, PAL_MODE_ALTERNATE(5));
    palSetPadMode(GPIOC, 3 , PAL_MODE_ALTERNATE(5));

    palSetPadMode(AUDIO_IO,AUDIO_L,PAL_MODE_OUTPUT_PUSHPULL);
    palSetPadMode(AUDIO_IO,AUDIO_R,PAL_MODE_OUTPUT_PUSHPULL);

    palClearPad(AUDIO_IO,AUDIO_L);
    palClearPad(AUDIO_IO,AUDIO_R);

    ht_audio_DisableCh();
}

void ht_audio_Zero(void){
    uint16_t i;
    for(i=0;i<TOTAL_BUFF_SIZE;i++){
        i2s_tx_buf[i] = 0;
    }
}

void ht_audio_Tone(double freq, double ampl){
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

void ht_audio_ToneNoAtt(double freq, double ampl){
    uint16_t i;
    uint16_t buffsize;
    double ysin;

    buffsize = (uint16_t) I2S_BUFF_SIZE/freq;

    // checking lowest possible amplitude
    double ampl_act;
    ampl_act = ampl*32767;
    if(ampl_act<=DEFAULT_AMPL_THD){ampl = 0;}

    ht_audio_Zero();

    for(i=0;i<buffsize;i++){
        ysin = ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));

#if WEIRD_SINE
          if(ysin >= 0){
              i2s_tx_buf[i]=ysin+32767;
  #if USE_STEREO_ARRAY
              i2s_tx_buf[i+1]=ysin+32767;
  #endif
          }
          if(ysin < 0){
              i2s_tx_buf[i]=ysin+32767;
  #if USE_STEREO_ARRAY
              i2s_tx_buf[i+1]=ysin+32767;
  #endif
          }
#else
        i2s_tx_buf[i] = ysin;
#endif
    }

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
    palClearPad(AUDIO_IO,AUDIO_L);
    palClearPad(AUDIO_IO,AUDIO_R);
}

void ht_audio_LeftCh(void){
    ht_audio_DisableCh();
    palSetPad(AUDIO_IO,AUDIO_L);
}

void ht_audio_RightCh(void){
    ht_audio_DisableCh();
    palSetPad(AUDIO_IO,AUDIO_R);
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
}

/** @} */
