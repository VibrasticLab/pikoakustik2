/**
 * @file    ht_mmc.h
 * @brief   MMC-SPI FAT-FS header.
 *
 * @addtogroup Storage
 * @{
 */

#ifndef HT_MMC_H
#define HT_MMC_H

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MMC_SPI_OK      0
#define MMC_SPI_FAIL    1
#define MMC_SPI_ERROR   2

#define LS_NOSHOW       0
#define LS_SHOWNUM      1
#define LS_JSONNUM      2
#define LS_SHOWLIST     3

#define CAT_SINGLE_LINE 0
#define CAT_MULTI_LINE  1

/**
 * @brief File buffer maximal size
 * @details More than 256 cause all system freeze
 */
#define MMC_STR_BUFF_SIZE 128

/**
 * @brief Filename string size
 */
#define MMC_FNAME_SIZE    16

/**
 * @brief Maximum Last Number to be saved
 */
#define FILE_MAX_NUM  250

/**
 * @brief Audiometri saving buffer size
 */
#define METRI_BUFFER_SIZE 2048

/**
 * @brief rename to match name f_write()
 */
#define f_readline    f_gets

/**
 * @brief For easy remember, chsnprintf() also defined as ht_mmc_Buff()
 */
#define ht_mmc_Buff chsnprintf

/**
 * @brief Small delay to give time for MMC
 */
#define ht_mmc_Delay() chThdSleepMicroseconds(100)

/**
 * @brief Check MMC readyness
 */
void ht_mmc_InitCheck(void);

/**
 * @brief Initialize MMC-SPI peripherals
 */
void ht_mmc_Init(void);

/**
 * @brief Test Write and Read Simple text in Append mode
 */
void ht_mmc_testWrite(void);

/**
 * @brief Test CAT on Simple text
 */
void ht_mmc_testCat(void);

/**
 * @brief List files on directory
 * @param Show option (0: No List, 1: File number, 2: File names)
 *
 */
void ht_mmc_lsFiles(uint8_t showList);

/**
 * @brief Read a file on directory and print
 * @param[in] uint16_t Last number of Save file
 * @param[in] uint8_t Whether using Multiple or Single line
 */
void ht_mmc_catFiles(uint16_t fnum, uint8_t lineType);


/**
 * @brief Read a file on a directory and load to a JSON string
 * @param[in] uint16_t Last number of Save file
 * @param[in] char* JSON string
 */
void ht_mmc_catFilesBuffer(uint16_t fnum, char *jsonbuff);

/*******************************************/

/**
 * @brief Check save file existence before audiometri
 * @details If last number file already exist, create new in incremented last number
 * @details Otherwise, use current last number
 * @details Save/Add "audiogram" on save/buffer files
 */
void ht_mmcMetri_chkFile(void);

/**
 * @brief Dump/Save Buffer into MMC
 */
void ht_mmcMetri_bufferSave(void);

/**
 * @brief Ordering File for Buffer into MMC
 */
void ht_mmcMetri_bufferOrder(void);

/*
 * @brief Show Buffer content
 */
void ht_mmcMetri_bufferShow(void);


/*******************************************/

/**
 * @brief Put JSON open bracket on save buffer
 * @param[in] uint8_t Channel number
 */
void ht_mmcOnceMetri_jsonChStart(uint8_t lr_ch);

/**
 * @brief Put JSON close bracket on save buffer
 */
void ht_mmcOnceMetri_jsonChClose(void);

/**
 * @brief Put JSON comma separator on save buffer
 */
void ht_mmcOnceMetri_jsonComma(void);

/**
 * @brief Add to buffer last amplification scale for every frequency test
 * @param[in] double Frequency ratio
 * @param[in] uint8_t Frequency index number
 * @param[in] uint8_t Amplitude scaling number
 */
void ht_mmcOnceMetri_hearingResult(double freq, uint8_t freqidx, uint8_t ample);

/**
 * @brief Add to array array of result record
 * @param[in] uint8_t Result array
 * @param[in] uint8_t Last index to fill in
 * @param[in] uint8_t Last Amplitude scale
 */
void ht_mmcOnceMetri_hearingRecord(uint8_t *resArray, uint8_t lastIdx, uint8_t lastAmpl);

/**
 * @brief Put JSON end bracket on save buffer
 */
void ht_mmcOnceMetri_jsonEnd(void);


/**
 * @brief Get Last Number of of record files
 * @return uint16_t File Number to check
 */
uint16_t ht_mmc_getLastNum(void);

#endif // HT_MMC_H

/** @} */
