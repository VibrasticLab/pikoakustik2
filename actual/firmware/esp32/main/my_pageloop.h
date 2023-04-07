/**
 * @file my_pageloop.h
 * @brief Page Loop header
 *
 * @addtogroup LCD
 * @{
 */

#ifndef MY_PAGELOOP_H
#define MY_PAGELOOP_H

/**
 * @brief Page Home index number
 *
 */
#define PAGE_HOME   0

/**
 * @brief Page Files index number
 *
 */
#define PAGE_FILE   1

/**
 * @brief Page PTA index number
 *
 */
#define PAGE_PTA    2

/**
 * @brief Maximum page index number
 *
 */
#define PAGE_MAX    PAGE_PTA

/**
 * @brief Page sending index number
 *
 */
#define PAGE_SEND   PAGE_MAX+1

void my_pageLoop(void);

#endif // MY_PAGELOOP_H

/** @} */
