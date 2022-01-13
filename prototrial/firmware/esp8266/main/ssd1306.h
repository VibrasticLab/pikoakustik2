/**
 * Original Works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/include/ssd1306.h
 */

#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include <stdbool.h>

#define PANEL_ACTIVE 0

typedef enum
{
    SSD1306_COLOR_TRANSPARENT = -1, //!< Transparent (not drawing)
    SSD1306_COLOR_BLACK = 0,        //!< Black (pixel off)
    SSD1306_COLOR_WHITE = 1,        //!< White (or blue, yellow, pixel on)
    SSD1306_COLOR_INVERT = 2,       //!< Invert pixel (XOR)
} ssd1306_color_t;

bool ssd1306_init(uint8_t id);
void ssd1306_term(uint8_t id);
void ssd1306_clear(uint8_t id);
void ssd1306_refresh(uint8_t id, bool force);

uint8_t ssd1306_get_width(uint8_t id);
uint8_t ssd1306_get_height(uint8_t id);

void ssd1306_draw_pixel(uint8_t id, int8_t x, int8_t y, ssd1306_color_t color);
void ssd1306_draw_hline(uint8_t id, int8_t x, int8_t y, uint8_t w, ssd1306_color_t color);
void ssd1306_draw_vline(uint8_t id, int8_t x, int8_t y, uint8_t h, ssd1306_color_t color);

void ssd1306_draw_rectangle(uint8_t id, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color);
void ssd1306_fill_rectangle(uint8_t id, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color);

void ssd1306_draw_circle(uint8_t id, int8_t x0, int8_t y0, uint8_t r, ssd1306_color_t color);
void ssd1306_fill_circle(uint8_t id, int8_t x0, int8_t y0, uint8_t r, ssd1306_color_t color);

void ssd1306_select_font(uint8_t id, uint8_t idx);
uint8_t ssd1306_draw_char(uint8_t id, uint8_t x, uint8_t y, unsigned char chr, ssd1306_color_t foreground, ssd1306_color_t background);
uint8_t ssd1306_draw_string(uint8_t id, uint8_t x, uint8_t y, char *str, ssd1306_color_t foreground, ssd1306_color_t background);

uint8_t ssd1306_measure_string(uint8_t id, char *str);
uint8_t ssd1306_get_font_height(uint8_t id);
uint8_t ssd1306_get_font_c(uint8_t id);

void ssd1306_invert_display(uint8_t id, bool invert);
void ssd1306_update_buffer(uint8_t id, uint8_t* data, uint16_t length);

#endif // SSD1306_H
