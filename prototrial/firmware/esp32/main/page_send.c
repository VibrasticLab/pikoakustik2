/**
 * @file page_send.c
 * @brief Page Send source
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

extern ssd1306_t oled_dev;
extern uint8_t pageNum;
extern bool pageSWable;

/**
 * @brief LCD buffer array
 *
 */
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

/**
 * @brief Page sending demo
 *
 */
void page_sendDisplay(uint8_t sendStep){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                        0, 0, "Preparing sending",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    if(sendStep>=PAGE_SEND_TRY){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 12, "Trying to send",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    if(sendStep>=PAGE_SEND_WAIT){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 24, "Waiting Response",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    if(sendStep>=PAGE_SEND_OK){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 36, "Completing",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

void page_send(void){
    page_sendDisplay(PAGE_SEND_PREP);
    send_DataGETDemo();
    pageNum = PAGE_HOME;
    pageSWable = true;
}

/** @} */