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

#define HT_STATE_PREP 0
#define HT_STATE_IDLE 1
#define HT_STATE_RUN  2

/**
 * @brief Response if ESP32 asking about current status
 * @param chp
 * @param argc
 * @param argv
 */
void esp32_MsgStatus(BaseSequentialStream *chp, int argc, char *argv[]);

/**
 * @brief Sending info to ESP32 about current status
 * @param status
 */
void esp32_InfoStatus(uint8_t status);

#endif // MSG_MY_H

/** @} */
