/**
 * @file    ht_metri.c
 * @brief   Audiometri process code.
 *
 * @addtogroup Audiometri
 * @{
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "ht_config.h"

#include "ht_audio.h"
#include "ht_metri.h"
#include "ht_console.h"

/**
 * @brief Device mode variable
 */
uint8_t mode_status = STT_IDLE;

/**
 * @brief Audiometri step variable
 */
uint8_t mode_step = STEP_ASK;

/**
 * @brief User response number
 */
uint8_t numresp;

/**
 * @brief User asking number
 */
uint8_t numask;

/**
 * @brief Counter for test in each frequency
 * @details Should be not exceed 50 as it will exhausting
 */
uint8_t test_count = 0;

/**
 * @brief Global flag for last answer status
 * @details Either False:0 or True:1
 */
uint8_t test_answer;

/**
 * @brief Channel status variable
 */
uint8_t channel_stt=OUT_LEFT;

/**
 * @brief Variable indicate amplitude scale going down
 */
static uint8_t curr_goDown = 1;

/**
 * @brief Varable indicate amplitude previously going down
 */
static uint8_t prev_goDown = 1;

/**
 * @brief Variable counting how much amplitude going up after down
 */
static uint8_t upAfterDown = 0;

/**
 * @brief calibrated array ratio for frequency
 * @details Last Calibrated: 1.25 = 500 Hz
 * @details Requirement: 250,500,1000,2000,4000,8000
 */

#if USER_METRI_ALLFREQ
static double freq_test[] = {0.625, 1.25, 2.5, 5, 10, 20};
#else
 #if USER_METRI_ONEFREQ
static double freq_test[] = {2.5};
 #else
static double freq_test[] = {1.25, 2.5, 5};
 #endif
#endif

/**
 * @brief Amplification ratio
 */
static double ampl_test = FIRSTTEST_DB;

/**
 * @brief Amplification number status
 */
static uint8_t ampl_num = 9;

/**
 * @brief Frequency array ID
 */
static uint8_t freq_idx = 0;

/**
 * @brief Array to record of result
 */
static uint8_t res_arr[TEST_MAX_COUNT];

/*******************************************/

/**
 * @brief Resetting Result record
 */
static void ht_metri_ResultReset(void){
    uint8_t i;

    for(i=0;i<TEST_MAX_COUNT;i++){
        res_arr[i] = 9;
    }
}

/**
 * @brief Audio Play function
 * @details Played in Metri routine
 */
static void ht_metri_AudioPlay(uint8_t lr_stt){
    ht_audio_Tone(freq_test[freq_idx],ampl_test);

    if(lr_stt==OUT_LEFT)ht_audio_LeftCh();
    else if(lr_stt==OUT_RIGHT) ht_audio_RightCh();

    ht_audio_Play(TEST_DURATION);
    ht_audio_DisableCh();
}

/* More action/statement need more allocated memory space */
static THD_WORKING_AREA(waRunMetri, 2048);
#define ThdFunc_RunMetri THD_FUNCTION

/**
 * @brief Thread for Audiometri process
 * @details Main thread that run Audiometri process
 */
static ThdFunc_RunMetri(thdRunMetri, arg) {
  (void)arg;

  uint8_t rndask;

  uint8_t freq_max = sizeof(freq_test)/sizeof(freq_test[0]);
  char strbuff[COMM_BUFF_SIZE];

  chRegSetThreadName("audiometri");

  while(true){
    chThdSleepMilliseconds(100);
  }
}

uint8_t ht_metri_RndOpt(void){
    char strbuff[COMM_BUFF_SIZE];
    uint8_t rndnum=0, rndnumask=0;

    //is this pseudorandom really works?
    srand((unsigned long)chVTGetSystemTime());

#if USER_METRI_LONGRNG
    uint8_t last_rnd;

    rndnum = rand() % 36;
    while(rndnum==last_rnd){rndnum = rand() % 36;}
    last_rnd = rndnum;

    if(rndnum==0||rndnum==5||rndnum==7||rndnum==11||rndnum==13||rndnum==17||rndnum==20||rndnum==21||rndnum==25||rndnum==29||rndnum==31||rndnum==35){
        rndnumask = OPT_ASK_A;
        ht_commUSB_Msg("Option A ");
    }
    else if(rndnum==1||rndnum==3||rndnum==8||rndnum==9||rndnum==14||rndnum==15||rndnum==18||rndnum==22||rndnum==26||rndnum==27||rndnum==32||rndnum==33){
        rndnumask = OPT_ASK_B;
        ht_commUSB_Msg("Option B ");
    }
    else if(rndnum==2||rndnum==4||rndnum==6||rndnum==10||rndnum==12||rndnum==16||rndnum==19||rndnum==23||rndnum==24||rndnum==28||rndnum==30||rndnum==34){
        rndnumask = OPT_ASK_C;
        ht_commUSB_Msg("Option C ");
    }
#else
    rndnum = rand() % 3;
    if(rndnum==0){rndnumask = OPT_ASK_A;ht_commUSB_Msg("Option A ");}
    if(rndnum==1){rndnumask = OPT_ASK_B;ht_commUSB_Msg("Option B ");}
    if(rndnum==2){rndnumask = OPT_ASK_C;ht_commUSB_Msg("Option C ");}
#endif

    ht_comm_Buff(strbuff,sizeof(strbuff),"(%1i)\r\n", rndnum);
    ht_commUSB_Msg(strbuff);

    return rndnumask;
}

void ht_metri_Init(void){
    chThdCreateStatic(waRunMetri, sizeof(waRunMetri), NORMALPRIO, thdRunMetri, NULL);
}

/** @} */
