/**
 * @file page_loop.h
 * @brief Page Loop header
 * 
 * @addtogroup LCD
 * @{
 */

#ifndef PAGE_LOOP_H
#define PAGE_LOOP_H

/**
 * @brief Page Home index number
 * 
 */
#define PAGE_HOME   0

/**
 * @brief Page Files index number
 * 
 */
#define PAGE_FILES  1

/**
 * @brief Page Plot index number
 * 
 */
#define PAGE_PLOT   2

/**
 * @brief Maximum page index number
 * 
 */
#define PAGE_MAX    PAGE_PLOT

/**
 * @brief Page sending index number
 * 
 */
#define PAGE_SEND   PAGE_MAX+1

void start_page(void);

#endif // PAGE_LOOP_H

/** @} */