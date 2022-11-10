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
#include "ff.h"

#include "chprintf.h"

#include "ht_config.h"

#include "ht_led.h"
#include "ht_mmc.h"
#include "ht_btn.h"
#include "ht_audio.h"
#include "ht_metri.h"
#include "ht_console.h"

#include "msg_my.h"

extern uint8_t mode_led;

extern FRESULT mmc_check_status;

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
 * @brief Frequency Counter for Progress
 */
uint8_t freq_count = 0;

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
 * @brief Variable counting false in rows
 */
static uint8_t falseInRows = 0;

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
static double freq_test[] = {1.25, 2.5, 5, 10};
 #endif
#endif

/**
 * @brief Amplification ratio
 */
static double ampl_test = FIRSTTEST_DB;

/**
 * @brief Amplification number status
 */
static uint8_t ampl_num = AMPL_SCALE_USED;

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
        res_arr[i] = AMPL_SCALE_USED;
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

static THD_WORKING_AREA(waRunMetri, MAX_THD_HEAP_SIZE);
#define ThdFunc_RunMetri THD_FUNCTION

/**
 * @brief Thread for Audiometri process
 * @details Main thread that run Audiometri process
 * @warning MMC still very problematic and can cause file bomb while this loop freezed
 * @warning This thread is the most easily freezed
 */
static ThdFunc_RunMetri(thdRunMetri, arg) {
    (void)arg;

    uint8_t rndask;

    uint8_t freq_max = sizeof(freq_test)/sizeof(freq_test[0]);

#if USER_METRI_USELOG
    char strbuff[COMM_BUFF_SIZE];
#endif

    chRegSetThreadName("audiometri");

    while (true) {
        if(mode_status==STT_SETUP){
            chThdSleepMilliseconds(100);

#if USER_METRI_USELOG
            ht_commUSB_Msg("Entering Mode: Ready\r\n");
#endif

            mode_status = STT_READY;
        }

        else if(mode_status==STT_CFILE){

            ht_metri_ResultReset();
#if USER_MMC
 #if USER_METRI_RECORD
            ht_mmc_InitCheck();
            if(mmc_check_status==FR_OK){
              ht_mmcMetri_chkFile();
            }
            else{
  #if USER_METRI_USELOG
              ht_commUSB_Msg("MMC Failed\r\n");
  #endif
            }

            ht_mmcOnceMetri_jsonChStart(channel_stt);
 #endif
#endif

#if USER_METRI_USELOG
            ht_commUSB_Msg("Entering Mode: Audiometri\r\n");
            ht_commUSB_Msg("------------\r\n");
#endif

#if USER_METRI_ENABLED
 #if USER_MMC
  #if USER_METRI_RECORD
            if(mmc_check_status==FR_OK){
  #else
            if(mode_status!=STT_METRI){
  #endif
 #endif

                freq_count = 0;
                ht_metri_Progress(freq_count);

                mode_led=LED_METRI;
                mode_status=STT_METRI;

  #if USER_ESP32
    #if USER_ESPIOSTT
                my_iosttSTMrun(TRUE);
    #endif
  #endif

            }
#else
            mode_status = STT_IDLE;
            mode_led = LED_READY;
#endif
        }

        else if(mode_status==STT_METRI || mode_status==STT_VIRT){
            if(mode_step==STEP_ASK){
                rndask = ht_metri_RndOpt();

                chThdSleepMilliseconds(2*TEST_SPEED_DELAY);
                led_answer_off();

                /*************************************/
                led_answerA();
                if(rndask == OPT_ASK_A){
                    ht_metri_AudioPlay(channel_stt);
                    numask = BTN_ANS_A;
                }
                chThdSleepMilliseconds(TEST_SPEED_DELAY);
                led_answer_off();
                /*************************************/

                chThdSleepMilliseconds(TEST_SPEED_DELAY);

                /*************************************/
                led_answerB();
                if(rndask == OPT_ASK_B){
                    ht_metri_AudioPlay(channel_stt);
                    numask = BTN_ANS_B;
                }
                chThdSleepMilliseconds(TEST_SPEED_DELAY);
                led_answer_off();
                /*************************************/

                chThdSleepMilliseconds(TEST_SPEED_DELAY);

                /*************************************/
                led_answerC();
                if(rndask == OPT_ASK_C){
                    ht_metri_AudioPlay(channel_stt);
                    numask = BTN_ANS_C;
                }
                chThdSleepMilliseconds(TEST_SPEED_DELAY);
                led_answer_off();
                /*************************************/

                if(mode_status==STT_VIRT){
                    numresp = numask;
                    mode_step=STEP_CHK;
                }
                else{
                    mode_step=STEP_WAIT;
                }

#if USER_METRI_USELOG
                ht_comm_Buff(strbuff,sizeof(strbuff),"freq,ampl: %6.3f, %i\r\n",freq_test[freq_idx],ampl_num);
                ht_commUSB_Msg(strbuff);
#endif

            }

            else if(mode_step==STEP_CHK){
                if(numresp==numask){
                    led_result_off();
                    led_resultYES();
                    test_answer = 1;
                    falseInRows = 0;
#if USER_METRI_USELOG
                    ht_commUSB_Msg("Answer is True\r\n");
#endif
                }
                else{
                    led_result_off();
                    led_resultNO();
                    test_answer = 0;
                    falseInRows++;
#if USER_METRI_USELOG
                    ht_commUSB_Msg("Answer is False\r\n");
#endif
                }

                numask = 0;
                numresp = 0;
                chThdSleepMilliseconds(500);

                led_answer_off();
                led_result_off();
                mode_step=STEP_ASK;

                // TODO: redefined on amplitude scaling method
                res_arr[test_count] = ampl_num;
                test_count++;

                if(test_answer==1){
                    if(ampl_num>0){
                        ampl_test = ampl_test / 2;
                        ampl_num--;
                        curr_goDown = 1;
                    }
                }
                else{
                    if(ampl_num<AMPL_SCALE_USED){
                        ampl_test = ampl_test * 2;
                        ampl_num++;
                        curr_goDown = 0;
                    }
                }

                // Some blind statistic here
                if((prev_goDown==1)&&(curr_goDown==0)){
                    upAfterDown++;
                }
                else if((prev_goDown==1)&&(curr_goDown==1)){
                    if(upAfterDown > (TEST_FALSE_COUNT-2))upAfterDown--;
                }
                prev_goDown = curr_goDown;
                // end of some stupidity

#if USER_METRI_TESTROW
                if(ampl_test <= SMALLEST_DB || test_count==TEST_MAX_COUNT || ampl_num==0 || upAfterDown==TEST_FALSE_COUNT || falseInRows>=3){
#else
                if(ampl_test <= SMALLEST_DB || test_count==TEST_MAX_COUNT || ampl_num==0 || upAfterDown==TEST_FALSE_COUNT){
#endif

                    if(curr_goDown==1){ampl_num++;}

#if USER_METRI_USELOG
                    ht_comm_Buff(strbuff,sizeof(strbuff),"Last Amplitude Scale=%i\r\n",ampl_num);
                    ht_commUSB_Msg(strbuff);
                    ht_commUSB_Msg("A Frequency Finish\r\n");
#endif

                    /* progress counter */
                    freq_count++;
                    ht_metri_Progress(freq_count);

#if USER_MMC
 #if USER_METRI_RECORD
                    ht_mmcOnceMetri_hearingResult(freq_test[freq_idx],freq_idx,ampl_num);
                    ht_mmcOnceMetri_hearingRecord(res_arr,test_count,ampl_num);
 #endif
#endif

                    freq_idx++;
                    ampl_test = FIRSTTEST_DB;
                    ampl_num = AMPL_SCALE_USED;
                    test_count = 0;
                    upAfterDown = 0;
                    ht_metri_ResultReset();

                    if(freq_idx != freq_max){
#if USER_METRI_USELOG
                        ht_commUSB_Msg("Continue next Frequency\r\n");
#endif

#if USER_MMC
 #if USER_METRI_RECORD
                        ht_mmcOnceMetri_jsonComma();
 #endif
#endif
                    }
                    else{
                        if(channel_stt!=OUT_RIGHT){
                            channel_stt = OUT_RIGHT;
                            freq_idx = 0;

#if USER_METRI_USELOG
                            ht_commUSB_Msg("Continue next Channel\r\n");
#endif


#if USER_MMC
 #if USER_METRI_RECORD
                            ht_mmcOnceMetri_jsonChClose();
                            ht_mmcOnceMetri_jsonChStart(channel_stt);
 #endif
#endif
                        }
                        else{
#if USER_MMC
 #if USER_METRI_RECORD
                            ht_mmcOnceMetri_jsonChClose();
                            ht_mmcMetri_endResult();
 #endif
#endif

/**************** Testing Finish **************/

#if USER_METRI_USELOG
                            ht_commUSB_Msg("\r\nTesting Finished\r\n");
#endif

                            freq_idx = 0;
                            mode_status = STT_IDLE;
                            mode_led = LED_READY;
                            channel_stt = OUT_LEFT;

                            freq_count = 0;
                            ht_metri_Progress(freq_count);


#ifdef PCB_P3
                            ht_audio_LeftCh();
#endif

#if USER_ESP32
  #if USER_ESPIOSTT
                            my_iosttSTMrun(FALSE);
  #endif
#endif
                        }
                    }
                }
            }
        }
        chThdSleepMilliseconds(100);
    }
}

void ht_metri_Progress(uint8_t progress_counter){
    char strProgress[10];

    uint8_t freq_count_max = 2 * sizeof(freq_test)/sizeof(freq_test[0]);;
    uint8_t freq_progress = (uint8_t) 100 * progress_counter/freq_count_max;

    ht_comm_Buff(strProgress, sizeof(strProgress), "aud %i\r\n",freq_progress);
    ht_commUSB_Msg(strProgress);
#if USER_ESP32
    ht_commUART_Msg(strProgress);
#endif
}

uint8_t ht_metri_RndOpt(void){
    uint8_t rndnum=0, rndnumask=0;

#if USER_METRI_USELOG
    char strbuff[COMM_BUFF_SIZE];
#endif

    //is this pseudorandom really works?
    srand((unsigned long)chVTGetSystemTime());

    rndnum = rand() % 3;
    if(rndnum==0){rndnumask = OPT_ASK_A;}
    if(rndnum==1){rndnumask = OPT_ASK_B;}
    if(rndnum==2){rndnumask = OPT_ASK_C;}

#if USER_METRI_USELOG
    ht_comm_Buff(strbuff,sizeof(strbuff),"(%1i)\r\n", rndnum);
    ht_commUSB_Msg(strbuff);
#endif

    return rndnumask;
}

void ht_metri_Init(void){
    chThdCreateStatic(waRunMetri, sizeof(waRunMetri), NORMALPRIO, thdRunMetri, NULL);
}

/** @} */
