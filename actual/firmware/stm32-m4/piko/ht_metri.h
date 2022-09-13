/**
 * @file    ht_metri.h
 * @brief   Audiometri process header.
 *
 * @addtogroup Audiometri
 * @{
 */

#ifndef HT_METRI_H
#define HT_METRI_H

#define STT_IDLE    0
#define STT_SETUP   1
#define STT_READY   2
#define STT_STDBY   3
#define STT_CFILE   4
#define STT_METRI   5
#define STT_VIRT    6

#define STEP_ASK    0
#define STEP_WAIT   1
#define STEP_CHK    2

#define OPT_ASK_A   0
#define OPT_ASK_B   1
#define OPT_ASK_C   2

/**
 * @brief Delay each event on metri loop
 */
#define TEST_SPEED_DELAY 500

/**
 * @brief Maximum number of false counter
 */
#define TEST_FALSE_COUNT 5

/**
 * @brief Maximum number false in row
 */
#define TEST_FALSE_INROW 3

/**
 * @brief Amplitude Scale for normal ears
 */
#define AMPL_SCALE_NORMAL 6

/**
 * @brief Amplitude Scale for actual ears
 */
#define AMPL_SCALE_ACTUAL 11

/**
 * @brief Start Amplitude scale for test
 */
#define AMPL_SCALE_USED   AMPL_SCALE_ACTUAL

/**
 * @brief Maximum number for each frequency test
 */
#define TEST_MAX_COUNT    24

/**
 * @brief Random number to choose answer position
 * @return Answer number position
 */
uint8_t ht_metri_RndOpt(void);

/**
 * @brief Audiometri process Initialization
 */
void ht_metri_Init(void);

#endif // HT_METRI_H

/** @} */
