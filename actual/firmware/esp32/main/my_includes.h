/**
 * @file my_includes.h
 * @brief Global header
 *
 * @addtogroup Main
 * @{
 */

/**
 * Just include everything necessary
 */

#ifndef _MY_INCLUDES_H_
#define _MY_INCLUDES_H_

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "driver/gpio.h"

#include "my_config.h"

#include "my_led.h"

#endif

 /** @} */