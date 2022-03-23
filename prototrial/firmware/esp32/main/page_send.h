/**
 * @file page_send.h
 * @brief Page Send header
 *
 * @addtogroup LCD
 * @{
 */

#ifndef PAGE_SEND_H
#define PAGE_SEND_H

#include "stdint.h"

#define PAGE_SEND_PREP  0
#define PAGE_SEND_TRY   1
#define PAGE_SEND_WAIT  2
#define PAGE_SEND_OK    3

void page_send(void);
void page_sendDisplay(uint8_t sendStep);

#endif // PAGE_SEND_H

/** @} */