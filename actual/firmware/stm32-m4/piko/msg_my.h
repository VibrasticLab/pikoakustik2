/**
 * @file    msg_my.h
 * @brief   ESP32 message package header.
 *
 * @addtogroup Console
 * @{
 */

#ifndef MSG_MY_H
#define MSG_MY_H

#include <stdint.h>

/* Status GPIO MACRO */
#define STATUS_MPAN_PIN 9 // PC.9 0: MPAN_OK | 1: MPAN_NO
#define STATUS_RDY_PIN  8 // PC.8 0: RDY_OK  | 1: RDY_NO
#define STATUS_BAT_PIN  7 // PC.7 0: BAT_OK  | 1: BAT_LOW
#define STATUS_RUN_PIN  6 // PC.6 0: IDLE    | 1: RUN

/**
 * @brief Set Ready Status IO
 * @details Value 0 means Not Ready and 1 means Ready
 *
 */
void my_iosttSTMready(uint8_t iostatus);

/**
 * @brief Set Run Status IO
 * @details Value 0 means Idle and 1 means Run
 *
 */
void my_iosttSTMrun(uint8_t iostatus);

/**
 * @brief Initiate GPIO Status group
 *
 */
void my_iosttInit(void);

#endif // MSG_MY_H

/** @} */
