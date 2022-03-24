/**
 * @file my_shell.h
 * @brief UART Shell header
 *
 * @addtogroup  Console
 * @{
 */

#ifndef _MY_SHELL_H_
#define _MY_SHELL_H_

#define UART_BUFF_SIZE 256

void shellInit(void);
int shellLoop(void);

#endif

/** @} */