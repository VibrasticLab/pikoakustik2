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

#define MY_USE_LED              TRUE    /* Whether LED subsystem activated or not */
#define MY_USE_NVS              TRUE    /* Always enable NVS subsystem */

#define MY_USE_UART             TRUE    /* Whether UART subsystem activated or not */
 #define MY_UART_USE_PROMPT     FALSE   /* Whether UART use shell prompt or not */
 #define MY_UART_SILENT         TRUE    /* Pull down IO15 for UART complete silent */
 #define MY_UART_DUMB           TRUE    /* Always use console in DUMB mode */

#define MY_USE_OLCD             TRUE    /* Whether use OLED LCD subsystem or not */


#endif

/** @} */
