/**
 * @file    ht_console.h
 * @brief   Console Shell header.
 *
 * @addtogroup Console
 * @{
 */

#ifndef HT_CONSOLE_H
#define HT_CONSOLE_H

/**
 * @brief Shell thread working area size
 * @details Set to bigger size if necessary
 */
#define SHELL_WA_SIZE   THD_WORKING_AREA_SIZE(2048)

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
 * @brief USBommon message function
 * @param[in] String Message to chprintf() on USB interface.
 */
void ht_commUSB_Msg(char *string);

#endif // HT_CONSOLE_H
/** @} */

