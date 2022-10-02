/**
 * @file my_btn.h
 * @brief GPIO Button header
 *
 * @addtogroup GPIO
 * @{
 */

#ifndef MY_BTN_H
#define MY_BTN_H

/**
 * @brief Switch Page Loop pin
 *
 */
#define BUTTON_PAGE_LOOP    27


/**
 * @brief Button action X
 * @details Home Page: Switch WiFi to Access-Point
 */
#define BUTTON_ACT_X        25 // BTN_ACT_A

/**
 * @brief Page control button input
 *
 */
#define PAGE_BUTTON_IN  ((1ULL<<BUTTON_PAGE_LOOP) | (1ULL<<BUTTON_ACT_X))

void my_btnInit(void);

#endif // MY_BTN_H

/** @} */
