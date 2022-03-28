/**
 * @file msg_ht.h
 * @brief STM32 message package header
 *
 * @addtogroup Console
 * @{
 */

#ifndef MSG_HT_H
#define MSG_HT_H

#define HT_ASK_STATE  0

#define HT_STATE_PREP 0
#define HT_STATE_IDLE 1
#define HT_STATE_RUN  2

void askingSTM32status(void);
void registerSTM32Messages(void);

#endif // MSG_HT_H

/** @} */
