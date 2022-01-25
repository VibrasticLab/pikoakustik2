/**
 * Just include everything necessary
 */

#ifndef _MY_INCLUDES_H_
#define _MY_INCLUDES_H_

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_system.h"
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "esp_sleep.h"
#include "esp_spi_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_err.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "driver/uart.h"
#include "rom/uart.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"

#include "fonts.h"
#include "ssd1306i2c.h"

#include "cmd_system.h"
#include "my_console.h"
#include "my_led.h"
#include "my_wifi.h"
#include "my_exti.h"
#include "lcd_draw.h"
#include "page_home.h"
#include "page_plot.h"
#include "page_files.h"
#include "page_loop.h"

#endif
