/**
 * @file    ht_console.h
 * @brief   Console Shell header.
 *
 * @addtogroup Console
 * @{
 */

#ifndef HT_CONSOLE_H
#define HT_CONSOLE_H

#include "ht_config.h"

/**
 * @brief Size off buffer for chsnprintf() on interface
 */
#define COMM_BUFF_SIZE 128

/**
 * @brief Shell thread working area size
 * @details Set to bigger size if necessary
 */
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(MAX_THD_HEAP_SIZE)

/**
 * @brief For easy remember, chsnprintf() defined as ht_comm_Buff()
 */
#define ht_comm_Buff chsnprintf

/**
 * @brief Start Shell and USB peripheral
 * @details Serial Interface using USB1 (SDU1)
 */
void ht_commUSB_Init(void);

/**
 * @brief Re-Initialize USB Shell Thread
 * @details This routine should be called on main thread with some delays
 */
void ht_commUSB_shInit(void);

/**
 * @brief USB Common message function
 * @param[in] String Message to chprintf() on USB interface.
 */
void ht_commUSB_Msg(char *string);

/**
 * @brief Start Shell and UART peripheral
 * @details Serial Interface using UART1 (SD1)
 */
void ht_commUART_Init(void);

/**
 * @brief Re-Initialize Shell Thread
 * @details This routine should be called on main thread with some delays
 */
void ht_commUART_shInit(void);

/**
 * @brief UART Common message function
 * @param[in] String Message to chprintf() on UART interface.
 */
void ht_commUART_Msg(char *string);

#endif // HT_CONSOLE_H
/** @} */

