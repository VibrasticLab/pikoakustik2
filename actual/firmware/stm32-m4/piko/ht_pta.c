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

uint8_t calAmpl[6][2];

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

void ht_ptaLoadArray(int id, char *jsonString){
    int i;
    int m=0,n=0;
    char val[3];

    for(i=1;i<id;i++){
        if (jsonEq(jsonString, &tkn[i], "ampl") == 0) {

            chsnprintf(val,sizeof(val),"%.*s\n",
                       tkn[i + 1].end - tkn[i + 1].start,
                       jsonString + tkn[i + 1].start);

            calAmpl[m][n] = atoi(val);

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

/** @} */

