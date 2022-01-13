/**
 * Original Works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/user/oled_fonts.c
 */

#include "my_includes.h"

extern const font_info_t glcd_5x7_font_info;
extern const font_info_t tahoma_8pt_font_info;

const font_info_t* oled_fonts[OLED_NUM_FONTS] = {
    &glcd_5x7_font_info,
    &tahoma_8pt_font_info
};
