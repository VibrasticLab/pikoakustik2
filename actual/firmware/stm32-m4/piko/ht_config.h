/**
 * @file ht_config.h
 * @brief Global configurations header
 * @addtogroup Main
 * @{
 */

#ifndef HT_INCLUDES_H
#define HT_INCLUDES_H

#define MAX_THD_HEAP_SIZE   4096   /* Maximum thread heap size (for metri and shell) */
#define METRI_HEAP_SIZE     MAX_THD_HEAP_SIZE

#define USER_SERIAL         TRUE   /* Whether enable serial interface or not */
 #define USER_SER_USB		TRUE   /* Whether enable USB part serial or not */
 #define USER_SER_UART		TRUE   /* Whether enable UART part serial or not */
 #define USER_USB_DESC      TRUE   /* Whether use custom USB description or not */
 #define USER_SER_SCALE     TRUE   /* Whether use tone test out in scale or not */
 #define USER_SER_BAUD		115200 /* Default Baudrate following ESP32*/

#define USER_MMC            TRUE   /* Whether use memory card or not */
 #define USER_MMC_MKFS      TRUE  /* Whether use disk formatting or not */
 #define USER_MMC_SAVE      TRUE   /* Whether MMC save result or not */
 #define USER_MMC_2SAVE     TRUE   /* Whether MMC save result twice or not */

#define USER_AUDIO          TRUE   /* Whether use Audio module or not */
 #define USER_AUDIO_TEST    TRUE  /* Whether use Audio test at startup */

#define USER_LED            TRUE   /* Whether use LED modules */
 #define USER_LED_RUN		FALSE  /* Whether use LED Run indicator or not */
#define USER_BUTTON         TRUE   /* Whether use Button modules */

#define USER_ESP32			TRUE   /* Whether use ESP32 modules */
 #define USER_ESPIOSTT      TRUE   /* Whether use GPIO status modules */

#define USER_METRI          TRUE   /* Whether use Audiometri routine or not */
 #define USER_METRI_ENABLED TRUE   /* Whether use RUN mode can be entered or not */
 #define USER_METRI_RECORD  TRUE   /* Whether record Audiometri session */
 #define USER_METRI_ALLFREQ TRUE   /* Whether Audiometri in all frequency or selection */
 #define USER_METRI_USELOG  TRUE   /* Whether metri loop use debug message */
 #define USER_METRI_ONEFREQ FALSE  /* Whether Audiometri in single frequency only */
 #define USER_METRI_TESTROW FALSE  /* Whether Audiometri use False In Row or not */

#endif // HT_INCLUDES_H

/** @} */
