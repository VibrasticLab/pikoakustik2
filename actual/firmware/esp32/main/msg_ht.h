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

#define PIN_STMSTT_RUN		19
#define PIN_STMSTT_READY	33

#define IO_STMSTT_IN ((1ULL<<PIN_STMSTT_READY) |                       \
						(1ULL<<PIN_STMSTT_RUN))

void msg_htiosttInit(void);

#endif // MSG_HT_H

/** @} */
