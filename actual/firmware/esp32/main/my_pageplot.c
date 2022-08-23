/**
 * @file my_pageplot.c
 * @brief Page Plot code
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

extern ssd1306_t oled_dev;
extern uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

void my_pagePlot(void){}

/**
 * @brief LCD plot X axis point example
 *
 */
static uint8_t xpoint[] = {10,25,40,55,70,85};

/**
 * @brief LCD plot y axis point example
 *
 */
static uint8_t ypoint[] = {10,30,15,25,30,35};

/**
 * @brief Plot Line
 *
 * @param x0 start X point
 * @param y0 start Y point
 * @param x1 end X point
 * @param y1 end Y point
 */
static void plot_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
    ssd1306_draw_line(&oled_dev,lcdbuff, x0,y0,x1,y1, OLED_COLOR_WHITE);
}

/**
 * @brief Draw plot axis
 *
 */
static void plot_axis(void){
    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_BITOCRA_4X7],
                        0, 0, "dB",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

   plot_line(5,8,5,58);

   ssd1306_draw_string(&oled_dev,
                       lcdbuff,
                       font_builtin_fonts[FONT_FACE_BITOCRA_4X7],
                       116, 55, "Hz",
                       OLED_COLOR_WHITE,
                       OLED_COLOR_BLACK);

  plot_line(5,58,114,58);
}

/**
 * @brief Draw demo plot
 *
 */
void my_pagePlot_demo(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    plot_axis();

    uint8_t idx;
    for(idx=0;idx<sizeof(xpoint)-1;idx++){
        plot_line(xpoint[idx],ypoint[idx],
                  xpoint[idx+1],ypoint[idx+1]);
    }

	ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/** @} */
