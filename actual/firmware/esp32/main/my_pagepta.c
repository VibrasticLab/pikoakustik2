/**
 * @file my_pagepta.c
 * @brief PTA display code
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

/**
 * Whether use strtok() method or not
 */
#define PTA_PARSE_STRTOK    FALSE

extern ssd1306_t oled_dev;
extern uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static uint8_t fileNum;
static uint8_t arrLPta[4];
static uint8_t arrRPta[4];

static void page_info_pta(const ssd1306_t *dev, uint8_t *fb, uint8_t fnum,  uint8_t *lPta, uint8_t *rPta){
    char strTitle[30];
    char strLPta[30];
    char strRPta[30];

    uint8_t LPta = (uint8_t) (lPta[0]+lPta[1]+lPta[2]+lPta[3])/4;
    uint8_t RPta = (uint8_t) (rPta[0]+rPta[1]+rPta[2]+rPta[3])/4;

    sprintf(strTitle, "PTA SUMMARY: %i", fnum);
    sprintf(strLPta, "L: (%i,%i,%i,%i) : %i", lPta[0], lPta[1], lPta[2], lPta[3], LPta);
    sprintf(strRPta, "R: (%i,%i,%i,%i) : %i", rPta[0], rPta[1], rPta[2], rPta[3], RPta);

    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 0, strTitle,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 20, strLPta,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 40, strRPta,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);
}

void my_ptaArrayReset(void){
    uint8_t i=0;

    fileNum = 0;
    for(i=0;i<4;i++){
        arrLPta[i] = 0;
        arrRPta[i] = 0;
    }
}

void my_ptaArrayLoad(char *csvArray){
#if PTA_PARSE_STRTOK
    char *pt;
    uint8_t i=0;

    pt = strtok(csvArray,",");
    while (pt != NULL) {
        if(i==0) fileNum = atoi(pt);
        else if((i>0) && (i<5)) arrLPta[i-1] = atoi(pt);
        else if(i>=5) arrRPta[i-5] = atoi(pt);

        i++;
        pt = strtok(NULL, ",");
    }
#else
    uint8_t i,j,cnt;
    char strSplit[9][4];

    j=0; cnt=0;
    for(i=0;i<=strlen(csvArray);i++){
        if(csvArray[i]==',' || csvArray[i]=='\0'){
            strSplit[cnt][j] = '\0';
            cnt++; j=0;
        }
        else{
            strSplit[cnt][j] = csvArray[i]; j++;
        }
    }

    for(i=0;i<cnt;i++){
        if(i==0) fileNum = atoi(strSplit[i]);
        else if((i>0) && (i<5)) arrLPta[i-1] = atoi(strSplit[i]);
        else if(i>=5) arrRPta[i-5] = atoi(strSplit[i]);
    }
#endif
}

void my_pagePta(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    page_info_pta(&oled_dev, lcdbuff, fileNum, arrLPta, arrRPta);
    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/** @} */
