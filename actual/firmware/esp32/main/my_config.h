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

#define MY_USE_NVS              TRUE    /* Always enable NVS subsystem */
#define MY_USE_LED              FALSE    /* Whether LED subsystem activated or not */
#define MY_USE_BTN              TRUE   /* Whether use Button one ESP32 or not */

#define MY_USE_UART             TRUE   /* Whether UART subsystem activated or not */
 #define MY_UART_SILENT         TRUE   /* Pull down IO15 for UART complete silent */
 #define MY_UART_NOLOG          TRUE   /* Whether use ESP-IDF log routines or not */
 #define MY_UART_DUMB           TRUE   /* Always use console in DUMB mode */
 #define MY_UART_NOPROMPT       TRUE   /* Whether UART use shell prompt or not */
 /*
 make sure update sdkconfig.defaults
 delete sdkconfig and run defconfig
 before re-building the app binary */
 #define MY_UART_NUM1           FALSE   /* Whether UART use NUM_1 or not */

#define MY_USE_OLCD             TRUE    /* Whether use OLED LCD subsystem or not */
 #define MY_PAGE_HOME           TRUE    /* Whether use Home Page Display or not */
 #define MY_PAGE_LOOP           TRUE    /* Whether use Loop Page Display or not */
 #define MY_PAGE_FILE           TRUE    /* Whether use File Page Display or not */
 #define MY_PAGE_PLOT           TRUE    /* Whether use Plot Page Display or not */

#define MY_USE_ADC              TRUE    /* Whether use ADC subsystem or not */
 #define MY_ADC_VCAL            FALSE   /* Whether use calibrated Vref or not */

#define MY_USE_I2SMIC           TRUE    /* Whether use I2S Mic or not */
 #define MY_MIC_TASK            TRUE    /* Whether use I2S Mic Task or not */
 #define MY_MIC_CMD             FALSE   /* Whether use I2S Mic command or not */

#define MY_USE_WIFI             TRUE    /* Whether use WiFi subsystem or not */
 #define MY_WIFI_AP             TRUE    /* Whether use WiFi as Access Point or not */
 #define MY_WIFI_STA            FALSE   /* Whether use WiFi as Client Station or not */
 #define MY_WIFI_ONCMD          TRUE    /* Whether use WiFi ON on command or not */
 #define MY_WIFI_ONBTN          FALSE   /* Whether use WiFi ON on button or not */

#define MY_USE_STM32			TRUE    /* Whether use STM32 subsystem or not */
 #define MY_STM32_IOSTATUS		TRUE    /* Whether use STM32 GPIO Status or not */

#define MY_USE_HTTPD            TRUE   /* Whether use HTTP server or not */
 #define HTTPD_START_ON_CONNECT FALSE  /* Whether HTTP server start/stop on connect/disconnect */
 #define MY_HTTP_ON_WIFIAP      TRUE   /* Whether HTTP start on WiFi AP start */
 #define MY_HTTP_ON_WIFISTA     FALSE  /* Whether HTTP start on WiFi STA start */
#endif

/** @} */
