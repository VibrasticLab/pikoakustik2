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
 * @brief Page control button input
 *
 */
#define PAGE_BUTTON_IN  ((1ULL<< BUTTON_PAGE_LOOP))

void my_btnInit(void);

#endif // MY_BTN_H

/** @} */
