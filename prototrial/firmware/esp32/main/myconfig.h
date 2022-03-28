/**
 * @file    myconfig.h
 * @brief   Global config header.
 *
 * @addtogroup Main
 * @{
 */

#ifndef _MY_CONFIG_H_
#define _MY_CONFIG_H_

/**
 * @brief LED Blink pin
 *
 */
#define BLINK_GPIO  2

/**
 * @brief LED Blink delay in ms
 *
 */
#define BLINK_DELAY 100

#define UART_BAUDRATE   38400

/**
 * @brief Whether Shell use prompt
 *
 */
#define UART_USE_PROMPT 0

/**
 * @brief Disable any unsuccesful command responses
 *
 */
#define UART_NO_ERROR_MSG 1

/**
 * @brief Use Console in dumb mode
 *
 */
#define CONSOLE_DUMB

#endif

/** @} */
