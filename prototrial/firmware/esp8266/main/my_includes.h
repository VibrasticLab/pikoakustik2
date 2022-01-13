/**
 * Just include everything necessary
 */

 #ifndef _MY_INCLUDES_H_
 #define _MY_INCLUDES_H_

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "esp_sleep.h"
#include "esp_spi_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/uart.h"
#include "rom/uart.h"

#include "driver/gpio.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"

#include "cmd_system.h"
#include "my_console.h"
#include "my_led.h"

 #endif
