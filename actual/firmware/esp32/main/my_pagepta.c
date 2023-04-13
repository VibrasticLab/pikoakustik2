/**
 * @file my_pagepta.c
 * @brief PTA display code
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

extern ssd1306_t oled_dev;
extern uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void page_info_pta(const ssd1306_t *dev, uint8_t *fb, uint8_t *lPta, uint8_t *rPta){
    char strLPta[30];
    char strRPta[30];

    uint8_t LPta = (uint8_t) (lPta[0]+lPta[1]+lPta[2]+lPta[3])/4;
    uint8_t RPta = (uint8_t) (rPta[0]+rPta[1]+rPta[2]+rPta[3])/4;

    sprintf(strLPta, "L: (%i,%i,%i,%i) : %i", lPta[0], lPta[1], lPta[2], lPta[3], LPta);
    sprintf(strRPta, "R: (%i,%i,%i,%i) : %i", rPta[0], rPta[1], rPta[2], rPta[3], RPta);

    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 0, "PTA SUMMARY:",
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

void my_pagePta(void){

}

void my_pagePta_demo(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    uint8_t arrLPta[] = {21,23,24,36};
    uint8_t arrRPta[] = {24,28,30,32};

    page_info_pta(&oled_dev, lcdbuff, arrLPta, arrRPta);
    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}


/** @} */
