/**
 * @file    ht_pta.h
 * @brief   Audiometri PTA header.
 *
 * @addtogroup Audiometri
 * @{
 */

#ifndef HT_PTA_H
#define HT_PTA_H

/**
 * @brief JSON Token Size
 * @details Bigger than this value will result variable overflow
 */
#define JSON_TOKEN_SIZE 512

/**
 * @brief ht_ptaParse
 * @param[in] char JSON Record string
 * @return int JSON Token Number
 */
int ht_ptaParse(char *jsonString);

/**
 * @brief ht_ptaParse
 * @param[in] int JSON Token Number
 * @param[in] char JSON Record string
 */
void ht_ptaLoadArray(int id, char *jsonString);

#endif // HT_PTA_H

/** @} */
