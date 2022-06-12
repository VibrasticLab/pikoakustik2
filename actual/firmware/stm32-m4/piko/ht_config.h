/**
 * @file ht_config.h
 * @brief Global configurations header
 * @addtogroup Main
 * @{
 */

#ifndef HT_INCLUDES_H
#define HT_INCLUDES_H

#define USER_BAUD           38400  /* Default Baudrate */

#define MAX_THD_HEAP_SIZE   4096   /* Maximum thread heap size (for metri and shell) */

#define USER_SERIAL         FALSE  /* Whether enable serial interface or not */
 #define USER_USB_DESC      TRUE   /* Whether use custom USB description or not */
 #define USER_SER_SCALE     TRUE   /* Whether use tone test out in scale or not */

/** MOST ANNOYING PART EVER */
#define USER_MMC            TRUE   /* Whether use memory card or not */

#define USER_AUDIO          TRUE   /* Whether use Audio module or not */
 #define USER_AUDIO_TEST    TRUE   /* Whether use Audio test at startup */

#define USER_LED            TRUE   /* Whether use LED modules */
#define USER_BUTTON         FALSE  /* Whether use Button modules */

#define USER_METRI          FALSE  /* Whether use Audiometri routine or not */
 #define USER_METRI_ENABLED FALSE  /* Whether use Audiometri can be entered or not */
 #define USER_METRI_RECORD  TRUE   /* Whether record Audiometri session */
 #define USER_METRI_RECONCE TRUE   /* Whether record written all at once or not. Keep enabled */
 #define USER_METRI_USELOG  TRUE   /* Whether metri loop use debug message */
 #define USER_METRI_ALLFREQ TRUE   /* Whether Audiometri in all frequency or selection */
 #define USER_METRI_ONEFREQ FALSE  /* Whether Audiometri in single frequency only */
 #define USER_METRI_LONGRNG FALSE  /* Whether use long rng method or simple */

#endif // HT_INCLUDES_H

/** @} */
