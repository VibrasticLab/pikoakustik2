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

#define STATUS_IO_0		2 // PB.2
#define STATUS_IO_1		3 // PB.3 (should always be high if connected to ESP32 IO-05)
#define STATUS_IO_2		4 // PB.4 (should always be low if connected to ESP32 IO-12)

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
