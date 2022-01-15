#include "my_includes.h"

extern ssd1306_t oled_dev;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static uint8_t battPercent = 100;

void page_home(void){
    char strBattPercent[16];

    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    sprintf(strBattPercent,"\x01%i%%",battPercent);
    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                        0, 0, strBattPercent,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}
