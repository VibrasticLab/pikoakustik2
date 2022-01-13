/**
 * Original works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/include/oled_fonts.h
 */

#ifndef FONTS_H
#define FONTS_H

#include <stdint.h>

typedef struct _font_char_desc
{
    uint8_t width;
    uint16_t offset;
} font_char_desc_t;

typedef struct _font_info
{
    uint8_t height;
    uint8_t c;
    char char_start;
    char char_end;
    const font_char_desc_t* char_descriptors;
    const uint8_t* bitmap;
} font_info_t;

#define OLED_NUM_FONTS 2

extern const font_info_t* oled_fonts[OLED_NUM_FONTS];

#endif // FONTS_H
