/**
 * @file    ht_pta.c
 * @brief   Audiometri PTA code.
 *
 * @addtogroup Audiometri
 * @{
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "ch.h"
#include "hal.h"

#include "chprintf.h"

#include "jsmn.h"

#include "ht_pta.h"
#include "ht_console.h"

extern uint16_t lastrec;

/**
 * @brief Amplitude Array to be Calibrated
 */
uint8_t calAmpl[6][2];

/**
 * @brief Calibrated PTA Array
 */
uint8_t calPTA[4][2];

/*****************************************************/

/**
 * @brief Calibration for JBL RETSPL-2 in dB-HL
 * @details Assumed that left and right channel are identical
 */
static uint8_t cal_JBL_RETSPL2[6][12] = {
    {0,7,9,10,13,18,24,30,36,42,48,54},
    {0,8,7,15,22,29,36,42,48,54,60,66},
    {0,7,7,14,21,28,34,41,47,53,59,65},
    {0,8,8,9,13,19,26,32,38,44,50,56},
    {0,7,6,7,8,12,18,24,30,36,42,48},
    {0,4,3,4,5,10,15,21,27,33,39,45}
};

/*****************************************************/

/**
 * @brief JSON Token Structure
 */
static jsmntok_t tkn[JSON_TOKEN_SIZE];

/**
 * @brief JSON Equal value search function
 * @param[in] char* jsonSTR
 * @param tok
 * @param str
 * @return
 */
static int jsonEq(const char *jsonSTR, jsmntok_t *tok, const char *str){

    if(tok->type==JSMN_STRING &&
      (int)strlen(str) == tok->end - tok->start &&
      strncmp(jsonSTR+tok->start, str, tok->end-tok->start)==0){

        return 0;
    }
    return -1;
}

/**
 * @brief Reset All Array
 */
static void ptaArrayReset(void){
    uint8_t i,j;

    for(i=0;i<2;i++){
        for(j=0;j<6;j++){
            calAmpl[j][i]=0;
        }
    }

    for(i=0;i<2;i++){
        for(j=0;j<4;j++){
            calPTA[j][i]=0;
        }
    }
}

/**
 * @brief Calibrate Array for PTA
 */
static void ptaArrayCalib(void){
    uint8_t idx;
    uint8_t i;

    // left channel
    for(i=0;i<4;i++){
        idx = calAmpl[i+1][0];
        if(idx>=12) idx=11;
        calPTA[i][0] = CALIBRATION_ARRAY[i+1][idx];
    }

    // right channel
    for(i=0;i<4;i++){
        idx = calAmpl[i+1][1];
        if(idx>=12) idx=11;
        calPTA[i][1] = CALIBRATION_ARRAY[i+1][idx];
    }
}

void ht_ptaLoadArray(int id, char *jsonString){
    int i;
    int m=0,n=0;
    char val[3];

    ptaArrayReset();

    for(i=1;i<id;i++){
        if (jsonEq(jsonString, &tkn[i], "ampl") == 0) {

            chsnprintf(val,sizeof(val),"%.*s\n",
                       tkn[i + 1].end - tkn[i + 1].start,
                       jsonString + tkn[i + 1].start);

            calAmpl[m][n] =(uint8_t) atoi(val);

            m++;
            if(m==6){
                m=0; n=1;
            }
        }
    }
}

int ht_ptaParse(char *jsonString){
  (void) jsonString;

  int jsonID;

  jsmn_parser jsonParser;
  jsmn_init(&jsonParser);

  jsonID = jsmn_parse(&jsonParser,
                      jsonString,
                      strlen(jsonString),
                      tkn, sizeof(tkn)/sizeof(tkn[0]));

  return jsonID;
}

void ht_ptaFinalCSV(uint16_t fnum, char *jsonPTA){
    uint8_t i,m=0,n=0;
    char ptaUnit[4];

    ptaArrayCalib();

    chsnprintf(jsonPTA,sizeof(jsonPTA),"%i,",fnum);

    for(i=0;i<8;i++){
        if(i<7) chsnprintf(ptaUnit,sizeof(ptaUnit),"%i,",calPTA[m][n]);
        else chsnprintf(ptaUnit,sizeof(ptaUnit),"%i",calPTA[m][n]);

        strcat(jsonPTA,ptaUnit);

        m++;
        if(m==4){
            m=0; n=1;
        }
    }
}

/** @} */

