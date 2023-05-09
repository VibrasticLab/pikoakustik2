/**
 * @file ht_cal.c
 * @brief Calibration Arrays code
 *
 * @addtogroup Audiometri
 * @{
 */

#include <stdio.h>
#include <stdlib.h>

#include "ch.h"
#include "hal.h"

#include "ht_cal.h"


/**
 * @brief Calibration in RETSPL2 for JBL Headphone
 */
uint8_t cal_RETSPL2_JBL[6][12]={
{0,7,9,10,13,18,24,30,36,42,48,54},
{0,8,7,15,22,29,36,42,48,54,60,66},
{0,7,7,14,21,28,34,41,47,53,59,65},
{0,8,8,9,13,19,26,32,38,44,50,56},
{0,7,6,7,8,12,18,24,30,36,42,48},
{0,4,3,4,5,10,15,21,27,33,39,45}
};

void ht_cal_ShowCalib(void){

}

/**  @} */


