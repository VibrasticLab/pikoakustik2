/**
 * @file    my_config.h
 * @brief   Global config header.
 *
 * @addtogroup Main
 * @{
 */

#ifndef _MY_CONFIG_H_
#define _MY_CONFIG_H_

#define TRUE    1
#define FALSE   0

#define MY_USE_LED              TRUE
#define MY_USE_NVS              TRUE

#define MY_USE_UART            TRUE
 #define MY_UART_USE_PROMPT    TRUE
 #define MY_UART_SILENT        FALSE  /* Pull down IO15 for UART0 complete silent */
 #define MY_UART_DUMB          TRUE

#endif

/** @} */