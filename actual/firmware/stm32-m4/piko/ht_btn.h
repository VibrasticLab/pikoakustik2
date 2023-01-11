/**
 * @file    ht_btn.h
 * @brief   Button routine header.
 *
 * @addtogroup GPIO
 * @{
 */

#ifndef HT_BTN_H
#define HT_BTN_H

/**
 * @brief Button answer A on port C0
 */
#define BTN_ANS_A 11

/**
 * @brief Button answer B on port C1
 */
#define BTN_ANS_B 12

/**
 * @brief Button answer C on port C2
 */
#define BTN_ANS_C 13

/**
 * @brief Wrong answer button
 */
#define BTN_WRONG 14

/**
 * @brief Button and their callbacks Initialization
 * @details Never put or calling any delay or chThdSleep() on PAL callbacks
 * @details By doing so would cause the entire system frozen
 */
void ht_btn_Init(void);

#endif // HT_BTN_H

/** @} */
