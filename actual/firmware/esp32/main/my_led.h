/**
 * @file my_led.h
 * @brief LED header
 *
 * @addtogroup GPIO
 * @{
 */

#ifndef _MY_LED_H_
#define _MY_LED_H_

#define MY_LED_GPIO    2
#define MY_LED_DELAY   500

/**
 * @brief Initialize LED subsystem
 *
 */
void my_ledInit(void);

/**
 * @brief Initialize LED subsystem as Disabled
 *
 */
void my_ledDisabled(void);

#endif

/** @} */
