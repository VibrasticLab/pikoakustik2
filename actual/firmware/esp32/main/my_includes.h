/**
 * @file my_includes.h
 * @brief Global header
 *
 * @addtogroup Main
 * @{
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

#include "esp_system.h"
#include "esp_log.h"
#include "esp_console.h"
#include "esp_vfs_dev.h"
#include "esp_sleep.h"
#include "esp_spi_flash.h"
#include "esp_event.h"
#include "esp_err.h"
#include "esp_now.h"
#include "esp_wifi.h"
#include "esp_tls.h"
#include "esp_http_client.h"

#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/dns.h"

#include "nvs.h"
#include "nvs_flash.h"

#include "driver/uart.h"
#include "esp32/rom/uart.h"
#include "linenoise/linenoise.h"
#include "argtable3/argtable3.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "my_config.h"

#include "fonts.h"
#include "ssd1306i2c.h"

#include "my_nvs.h"
#include "my_led.h"
#include "my_cmd.h"
#include "my_olcd.h"
#include "my_shell.h"
#include "my_wifiap.h"
#include "my_wifista.h"
#include "my_pagehome.h"

#include "msg_ht.h"

#endif

 /** @} */
