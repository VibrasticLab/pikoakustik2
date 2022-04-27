#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_AMPL_THD 1
#define I2S_BUFF_SIZE   512
#define TOTAL_BUFF_SIZE I2S_BUFF_SIZE*16
#define DEFAULT_ATTEN 1

uint16_t sineSize = 0;

#if WEIRD_SINE
uint16_t i2s_tx_buf[TOTAL_BUFF_SIZE];
#else
int16_t i2s_tx_buf[TOTAL_BUFF_SIZE];
#endif

static void tone_Zero(void){
    uint16_t i;
    for(i=0;i<TOTAL_BUFF_SIZE;i++){
        i2s_tx_buf[i] = 0;
    }
}

int main(int argc, char *argv[])
{

    uint16_t i;
    uint16_t buffsize;
    double ysin;

    double freq = (double) 500 / 400;
    double ampl = 1;

    buffsize = (uint16_t) I2S_BUFF_SIZE/freq;

    // checking lowest possible amplitude
    double ampl_act;
    ampl_act = DEFAULT_ATTEN*ampl*32767;
    if(ampl_act<=DEFAULT_AMPL_THD){ampl = 0;}

    for(i=0;i<buffsize;i++){
        ysin = DEFAULT_ATTEN*ampl*32767*sin(2*3.141592653589793*((double)i/(double)buffsize));

#if WEIRD_SINE
        if(ysin >= 0) i2s_tx_buf[i]=ysin;
        if(ysin < 0) i2s_tx_buf[i]=ysin+65535;
#else
        i2s_tx_buf[i] = ysin;
#endif
    }

    sineSize = buffsize;

#if WEIRD_SINE
    printf("use WEIRD SINE\r\n");
#else
    printf("use NORMAL SINE\r\n");
#endif

    printf("===============\r\n");

    for(i=0;i<sineSize;i++){
      printf("%d,",i2s_tx_buf[i]);
    }

    printf("\r\n===============\r\n");

    return 0;
}
