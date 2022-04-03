/**
 * @file ht_config.h
 * @brief Global configurations header
 * @addtogroup Main
 * @{
 */

#ifndef HT_INCLUDES_H
#define HT_INCLUDES_H

#define USER_BAUD           38400    /* Default Baudrate */

#define USER_SERIAL         TRUE   /* Whether enable serial interface or not */
 #define USER_USB_DESC      TRUE   /* Whether use custom USB description or not */
 #define USER_SER_SCALE     TRUE   /* Whether use tone test out in scale or not */

/** MOST ANNOYING PART EVER */
#define USER_MMC            TRUE   /* Whether use memory card or not */

#define USER_AUDIO          TRUE   /* Whether use Audio module or not */
 #define USER_AUDIO_TEST    TRUE   /* Whether use Audio test at startup */

#define USER_LED_BUTTON     TRUE   /* Whether use LED and Button modules */

#define USER_METRI          TRUE   /* Whether use Audiometri routine or not */
 #define USER_METRI_RECORD  TRUE   /* Whether record Audiometri session */
 #define USER_METRI_ALLFREQ FALSE  /* Whether Audiometri in all frequency or selection */
 #define USER_METRI_ONEFREQ FALSE  /* Whether Audiometri in single frequency only */
 #define USER_METRI_LONGRNG FALSE  /* Whether use long rng method or simple */
 #define USER_METRI_USELOG  FALSE  /* Whether metri loop use debug message. Keep disabled */

#endif // HT_INCLUDES_H

/** @} */
