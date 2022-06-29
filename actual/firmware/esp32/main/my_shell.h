/**
 * @file my_shell.h
 * @brief UART Shell header
 *
 * @addtogroup  Console
 * @{
 */

#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

/**
 * @brief UART baudrate value
 *
 */
#define MY_UART_BAUDRATE   38400

/**
 * @brief UART shell buffer size
 *
 */
#define MY_UART_BUFF_SIZE 1024

void my_shellInit(void);
int my_shellLoop(void);

#endif

/** @} */