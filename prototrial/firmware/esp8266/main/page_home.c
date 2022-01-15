#include "my_includes.h"

extern ssd1306_t oled_dev;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static uint8_t battPercent = 65;

static void page_batt_full(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,3,0,6,2,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,0,3,12,18,OLED_COLOR_WHITE);
}

static void page_batt_empty(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,3,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,0,3,12,18,OLED_COLOR_WHITE);
}

static void page_batt_half(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,3,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,0,3,12,9,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,0,11,12,9,OLED_COLOR_WHITE);
}

void page_home(void){
    char strBattPercent[16];

    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    if(battPercent>70){
        page_batt_full(&oled_dev,lcdbuff);
    }
    else if((battPercent<70) && (battPercent>40)){
        page_batt_half(&oled_dev,lcdbuff);
    }
    else if(battPercent<40){
        page_batt_empty(&oled_dev,lcdbuff);
    }

    sprintf(strBattPercent,"%3i%%",battPercent);
    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                        13, 0, strBattPercent,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}
