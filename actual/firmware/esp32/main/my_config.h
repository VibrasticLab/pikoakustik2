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

#define MY_USE_LED              FALSE   /* Whether LED subsystem activated or not */
#define MY_USE_NVS              TRUE    /* Always enable NVS subsystem */

#define MY_USE_UART             TRUE    /* Whether UART subsystem activated or not */
 #define MY_UART_USE_PROMPT     TRUE    /* Whether UART use shell prompt or not */
 #define MY_UART_SILENT         TRUE    /* Pull down IO15 for UART complete silent */
 #define MY_UART_NOLOG          TRUR    /* Whether use ESP-IDF log routines or not */
 #define MY_UART_DUMB           TRUE    /* Always use console in DUMB mode */

#define MY_USE_OLCD             TRUE    /* Whether use OLED LCD subsystem or not */
 #define MY_PAGE_HOME           TRUE    /* Whether use Home Page Display or not */

#define MY_USE_ADC              TRUE    /* Whether use ADC subsystem or not */
 #define MY_ADC_VCAL            TRUE    /* Whether use calibrated Vref or not */

#define MY_USE_WIFI             TRUE   /* Whether use WiFi subsystem or not */
 #define MY_WIFI_AP             FALSE   /* Whether use WiFi as Access Point or not */
 #define MY_WIFI_STA            TRUE    /* Whether use WiFi as Client Station or not */
 #define MY_WIFI_ONCMD          FALSE   /* Whether use WiFi ON on command or not */

#endif

/** @} */
