/**
 * @file my_pagefile.c
 * @brief Page File code
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

extern ssd1306_t oled_dev;
extern uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

void my_pageFile(void){}

/**
 * @brief File list display demo
 *
 */
void my_pageFile_demo(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    uint8_t fileNum=0;
    uint8_t ycurr = 0, yprev = 0;
    char strFileName[16];

    for(fileNum=0;fileNum<6;fileNum++){
        sprintf(strFileName,"File_%i.txt",fileNum);

        if(fileNum>0){
            yprev = ycurr;
            ycurr = yprev + 10;
        }

        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_GLCD5x7],
                            0, ycurr, strFileName,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/** @} */
