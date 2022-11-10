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
 * @brief Button Action Y
 * @details Home Page: Manual Buffer Save
 */
#define BUTTON_ACT_Y        26 // BTN_ACT_B

/**
 * @brief Page control button input
 *
 */
#define PAGE_BUTTON_IN  ((1ULL<<BUTTON_PAGE_LOOP) | (1ULL<<BUTTON_ACT_X) | (1ULL<<BUTTON_ACT_Y))

void my_btnInit(void);

#endif // MY_BTN_H

/** @} */
