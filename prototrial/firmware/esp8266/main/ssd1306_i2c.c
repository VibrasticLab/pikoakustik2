/**
 * Original works:
 * https://github.com/baoshi/ESP-I2C-OLED/blob/master/user/ssd1306_i2c.c
 */

#include "my_includes.h"

#define SSD1306_NONE       0  //!< not used
#define SSD1306_128x64     1  //!< 128x32 panel
#define SSD1306_128x32     2  //!< 128x64 panel

#define PANEL0_TYPE     SSD1306_128x64
#define PANEL0_ADDR     0x78 //(0x3c << 1)
#define PANEL0_USE_RST  false
#define PANEL0_RST_MUX
#define PANEL0_RST_FUNC
#define PANEL0_RST_BIT

typedef struct _oled_i2c_ctx
{
    uint8_t type;
    uint8_t address;
    uint8_t *buffer;
    uint8_t width;
    uint8_t height;
    uint8_t id;
    uint8_t refresh_top;
    uint8_t refresh_left;
    uint8_t refresh_right;
    uint8_t refresh_bottom;
    const font_info_t* font;
} oled_i2c_ctx;

static oled_i2c_ctx* _ctxs[2] = { NULL };

static void _command(uint8_t addr, uint8_t comm){
    bool ret;

    i2c_start();
    ret = i2c_write(addr);

    if(!ret) i2c_stop();

    i2c_write(0x00);
    i2c_write(comm);
    i2c_stop();
}

static void _data(uint8_t addr, uint8_t dat){
    bool ret;

    i2c_start();
    ret = i2c_write(addr);

    if(!ret) i2c_stop();

    i2c_write(0x40);
    i2c_write(dat);
    i2c_stop();
}

bool ssd1306_init(uint8_t id){
    oled_i2c_ctx *ctx = NULL;

    if ((id != 0) && (id != 1))  goto oled_init_fail;

    ssd1306_term(id);

    ctx = pvPortZalloc(sizeof(oled_i2c_ctx));
    if (ctx == NULL){
        printf("Alloc OLED context failed\r\n");
        goto oled_init_fail;
    }

    if (id == 0){
#if (PANEL0_TYPE != 0)
 #if (PANEL0_TYPE == SSD1306_128x64)
        ctx->type = SSD1306_128x64;
        ctx->buffer = pvPortZalloc(1024);
        ctx->width = 128;
        ctx->height = 64;
 #elif (PANEL0_TYPE == SSD1306_128x32)
        ctx->type = SSD1306_128x32;
        ctx->buffer = pvPortZalloc(512);
        ctx->width = 128;
        ctx->height = 32;
 #else
  #error "Panel 0 undefined"
 #endif

        if (ctx->buffer == NULL){
            printf("Alloc OLED buffer failed\r\n");
            goto oled_init_fail;
        }
        ctx->address = PANEL0_ADDR;

 #if PANEL0_USE_RST
        PIN_FUNC_SELECT(PANEL0_RST_MUX, PANEL0_RST_FUNC);
        GPIO_REG_WRITE(GPIO_ENABLE_ADDRESS, GPIO_REG_READ(GPIO_ENABLE_ADDRESS) | PANEL0_RST_BIT);
        GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, PANEL0_RST_BIT);
        os_delay_us(10000);
        GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, PANEL0_RST_BIT);
 #endif

#else
        dmsg_err_puts("Panel 0 not defined.");
        goto oled_init_fail;
#endif
    }
    else if(id == 1){
        printf("Panel 1 is not available for now\r\n");
    }

    i2c_start();
    if(!i2c_write(ctx->address)){
        i2c_stop();
        printf("OLED I2C bus not responding\r\n");
        goto oled_init_fail;
    }
    i2c_stop();

    if (ctx->type == SSD1306_128x64){
        _command(ctx->address, 0xae); // SSD1306_DISPLAYOFF
        _command(ctx->address, 0xd5); // SSD1306_SETDISPLAYCLOCKDIV
        _command(ctx->address, 0x80); // Suggested value 0x80
        _command(ctx->address, 0xa8); // SSD1306_SETMULTIPLEX
        _command(ctx->address, 0x3f); // 1/64
        _command(ctx->address, 0xd3); // SSD1306_SETDISPLAYOFFSET
        _command(ctx->address, 0x00); // 0 no offset
        _command(ctx->address, 0x40); // SSD1306_SETSTARTLINE line #0
        _command(ctx->address, 0x20); // SSD1306_MEMORYMODE
        _command(ctx->address, 0x00); // 0x0 act like ks0108
        _command(ctx->address, 0xa1); // SSD1306_SEGREMAP | 1
        _command(ctx->address, 0xc8); // SSD1306_COMSCANDEC
        _command(ctx->address, 0xda); // SSD1306_SETCOMPINS
        _command(ctx->address, 0x12);
        _command(ctx->address, 0x81); // SSD1306_SETCONTRAST
        _command(ctx->address, 0xcf);
        _command(ctx->address, 0xd9); // SSD1306_SETPRECHARGE
        _command(ctx->address, 0xf1);
        _command(ctx->address, 0xdb); // SSD1306_SETVCOMDETECT
        _command(ctx->address, 0x30);
        _command(ctx->address, 0x8d); // SSD1306_CHARGEPUMP
        _command(ctx->address, 0x14); // Charge pump on
        _command(ctx->address, 0x2e); // SSD1306_DEACTIVATE_SCROLL
        _command(ctx->address, 0xa4); // SSD1306_DISPLAYALLON_RESUME
        _command(ctx->address, 0xa6); // SSD1306_NORMALDISPLAY
    }

    else if (ctx->type == SSD1306_128x32){
        _command(ctx->address, 0xae); // SSD1306_DISPLAYOFF
        _command(ctx->address, 0xd5); // SSD1306_SETDISPLAYCLOCKDIV
        _command(ctx->address, 0x80); // Suggested value 0x80
        _command(ctx->address, 0xa8); // SSD1306_SETMULTIPLEX
        _command(ctx->address, 0x1f); // 1/32
        _command(ctx->address, 0xd3); // SSD1306_SETDISPLAYOFFSET
        _command(ctx->address, 0x00); // 0 no offset
        _command(ctx->address, 0x40); // SSD1306_SETSTARTLINE line #0
        _command(ctx->address, 0x8d); // SSD1306_CHARGEPUMP
        _command(ctx->address, 0x14); // Charge pump on
        _command(ctx->address, 0x20); // SSD1306_MEMORYMODE
        _command(ctx->address, 0x00); // 0x0 act like ks0108
        _command(ctx->address, 0xa1); // SSD1306_SEGREMAP | 1
        _command(ctx->address, 0xc8); // SSD1306_COMSCANDEC
        _command(ctx->address, 0xda); // SSD1306_SETCOMPINS
        _command(ctx->address, 0x02);
        _command(ctx->address, 0x81); // SSD1306_SETCONTRAST
        _command(ctx->address, 0x2f);
        _command(ctx->address, 0xd9); // SSD1306_SETPRECHARGE
        _command(ctx->address, 0xf1);
        _command(ctx->address, 0xdb); // SSD1306_SETVCOMDETECT
        _command(ctx->address, 0x40);
        _command(ctx->address, 0x2e); // SSD1306_DEACTIVATE_SCROLL
        _command(ctx->address, 0xa4); // SSD1306_DISPLAYALLON_RESUME
        _command(ctx->address, 0xa6); // SSD1306_NORMALDISPLAY
    }

    ctx->id = id;
    _ctxs[id] = ctx;

    _command(ctx->address, 0xaf);

    ssd1306_clear(id);
    ssd1306_refresh(id, true);

    return true;

oled_init_fail:
    if (ctx && ctx->buffer) free(ctx->buffer);
    if (ctx) free(ctx);
    return false;
}

void ssd1306_clear(uint8_t id){
    oled_i2c_ctx *ctx = _ctxs[id];

    if(ctx == NULL) return;

    if(ctx->type == SSD1306_128x64){
        memset(ctx->buffer, 0, 1024);
    }
    else if(ctx->type == SSD1306_128x32){
        memset(ctx->buffer, 0, 512);
    }

    ctx->refresh_right = ctx->width - 1;
    ctx->refresh_bottom = ctx->height - 1;
    ctx->refresh_top = 0;
    ctx->refresh_left = 0;
}

void ssd1306_refresh(uint8_t id, bool force){
    oled_i2c_ctx *ctx = _ctxs[id];

    uint8_t i,j;
    uint16_t k;
    uint8_t page_start, page_end;

    if(ctx == NULL) return;
    if(force){
        if(ctx->type == SSD1306_128x64){
            _command(ctx->address, 0x21); // SSD1306_COLUMNADDR
            _command(ctx->address, 0);    // column start
            _command(ctx->address, 127);  // column end
            _command(ctx->address, 0x22); // SSD1306_PAGEADDR
            _command(ctx->address, 0);    // page start
            _command(ctx->address, 7);    // page end (8 pages for 64 rows OLED)

            for (k = 0; k < 1024; k++){
                i2c_start();
                i2c_write(ctx->address);
                i2c_write(0x40);

                for (j = 0; j < 16; ++j){
                    i2c_write(ctx->buffer[k]);
                    ++k;
                }

                --k;
                i2c_stop();
            }
        }

        else if(ctx->type == SSD1306_128x32){
            _command(ctx->address, 0x21); // SSD1306_COLUMNADDR
            _command(ctx->address, 0);    // column start
            _command(ctx->address, 127);  // column end
            _command(ctx->address, 0x22); // SSD1306_PAGEADDR
            _command(ctx->address, 0);    // page start
            _command(ctx->address, 3);    // page end (4 pages for 32 rows OLED)

            for (k = 0; k < 512; k++){
                i2c_start();
                i2c_write(ctx->address);
                i2c_write(0x40);

                for (j = 0; j < 16; ++j){
                    i2c_write(ctx->buffer[k]);
                    ++k;
                }

                --k;
                i2c_stop();
            }
        }
    }

    else{
        if ((ctx->refresh_top <= ctx->refresh_bottom) && (ctx->refresh_left <= ctx->refresh_right)){
            page_start = ctx->refresh_top / 8;
            page_end = ctx->refresh_bottom / 8;

            _command(ctx->address, 0x21); // SSD1306_COLUMNADDR
            _command(ctx->address, ctx->refresh_left);    // column start
            _command(ctx->address, ctx->refresh_right);   // column end
            _command(ctx->address, 0x22); // SSD1306_PAGEADDR
            _command(ctx->address, page_start);    // page start
            _command(ctx->address, page_end); // page end

            k = 0;
            for (i = page_start; i <= page_end; ++i){
                for (j = ctx->refresh_left; j <= ctx->refresh_right; ++j){
                    if (k == 0){
                        i2c_start();
                        i2c_write(ctx->address);
                        i2c_write(0x40);
                    }

                    i2c_write(ctx->buffer[i * ctx->width + j]);
                    ++k;
                    if (k == 16){
                        i2c_stop();
                        k = 0;
                    }
                }
            }

            if (k != 0) i2c_stop();
        }
    }

    ctx->refresh_top = 255;
    ctx->refresh_left = 255;
    ctx->refresh_right = 0;
    ctx->refresh_bottom = 0;
}

void ssd1306_term(uint8_t id){
    oled_i2c_ctx *ctx = _ctxs[id];

    if(ctx == NULL) return;

    _command(ctx->address, 0xae);
    _command(ctx->address, 0x8d);
    _command(ctx->address, 0x10);

    if (ctx->buffer) free(ctx->buffer);
    free(ctx);

    _ctxs[id] = NULL;
}

uint8_t ssd1306_get_width(uint8_t id){
    oled_i2c_ctx *ctx = _ctxs[id];

    if (ctx == NULL) return 0;
    return ctx->width;
}

void ssd1306_draw_pixel(uint8_t id, int8_t x, int8_t y, ssd1306_color_t color){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint16_t index;

    if(ctx == NULL) return;

    if((x >= ctx->width) || (x < 0) || (y >= ctx->height) || (y < 0)) return;

    index = x + (y / 8) * ctx->width;

    switch (color){
        case SSD1306_COLOR_TRANSPARENT:
            break;
        case SSD1306_COLOR_WHITE:
            ctx->buffer[index] |= (1 << (y & 7));
            break;
        case SSD1306_COLOR_BLACK:
            ctx->buffer[index] &= ~(1 << (y & 7));
            break;
        case SSD1306_COLOR_INVERT:
            ctx->buffer[index] ^= (1 << (y & 7));
            break;
    }

    if (ctx->refresh_left > x) ctx->refresh_left = x;
    if (ctx->refresh_right < x) ctx->refresh_right = x;
    if (ctx->refresh_top > y) ctx->refresh_top = y;
    if (ctx->refresh_bottom < y) ctx->refresh_bottom = y;
}

void ssd1306_draw_hline(uint8_t id, int8_t x, int8_t y, uint8_t w, ssd1306_color_t color){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint16_t index;
    uint8_t mask, t;

    if (ctx == NULL) return;

    if ((x >= ctx->width) || (x < 0) || (y >= ctx->height) || (y < 0)) return;
    if (w == 0) return;
    if (x + w > ctx->width) w = ctx->width - x;

    t = w;
    index = x + (y / 8) * ctx->width;
    mask = 1 << (y & 7);

    switch (color){
        case SSD1306_COLOR_TRANSPARENT:
            break;
        case SSD1306_COLOR_WHITE:
            while (t--){
                ctx->buffer[index] |= mask;
                ++index;
            }
            break;
        case SSD1306_COLOR_BLACK:
            mask = ~mask;
            while (t--){
                ctx->buffer[index] &= mask;
                ++index;
            }
            break;
        case SSD1306_COLOR_INVERT:
            while (t--){
                ctx->buffer[index] ^= mask;
                ++index;
            }
            break;
    }

    if (ctx->refresh_left > x) ctx->refresh_left = x;
    if (ctx->refresh_right < x + w - 1) ctx->refresh_right = x + w - 1;
    if (ctx->refresh_top > y) ctx->refresh_top = y;
    if (ctx->refresh_bottom < y) ctx->refresh_bottom = y;
}

void ssd1306_draw_vline(uint8_t id, int8_t x, int8_t y, uint8_t h, ssd1306_color_t color){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint16_t index;
    uint8_t mask, mod, t;

    if (ctx == NULL) return;

    if ((x >= ctx->width) || (x < 0) || (y >= ctx->height) || (y < 0)) return;
    if (h == 0) return;
    if (y + h > ctx->height) h = ctx->height - y;

    t = h;
    index = x + (y / 8) * ctx->width;
    mod = y & 7;

    if(mod){
        // Magic from Adafruit
        mod = 8 - mod;
        static const uint8_t premask[8] = { 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE };
        mask = premask[mod];

        if (t < mod) mask &= (0xFF >> (mod - t));

        switch (color){
            case SSD1306_COLOR_TRANSPARENT:
                break;
            case SSD1306_COLOR_WHITE:
                ctx->buffer[index] |= mask;
                break;
            case SSD1306_COLOR_BLACK:
                ctx->buffer[index] &= ~mask;
                break;
            case SSD1306_COLOR_INVERT:
                ctx->buffer[index] ^= mask;
                break;
        }

        if (t < mod) goto draw_vline_finish;

        t -= mod;
        index += ctx->width;
    }

    if (t >= 8){ // byte aligned line at middle
        switch (color){
            case SSD1306_COLOR_TRANSPARENT:
                break;
            case SSD1306_COLOR_WHITE:
                do{
                   ctx->buffer[index] = 0xff;
                   index += ctx->width;
                   t -= 8;
                }while (t >= 8);
                break;
            case SSD1306_COLOR_BLACK:
                do{
                   ctx->buffer[index] = 0x00;
                   index += ctx->width;
                   t -= 8;
                } while (t >= 8);
                break;
            case SSD1306_COLOR_INVERT:
                do{
                    ctx->buffer[index] = ~ctx->buffer[index];
                    index += ctx->width;
                    t -= 8;
                } while (t >= 8);
                break;
        }
    }

    if (t){ // // partial line at bottom
        mod = t & 7;
        static const uint8_t postmask[8] = {0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F };
        mask = postmask[mod];

        switch (color){
            case SSD1306_COLOR_TRANSPARENT:
                break;
            case SSD1306_COLOR_WHITE:
                ctx->buffer[index] |= mask;
                break;
            case SSD1306_COLOR_BLACK:
                ctx->buffer[index] &= ~mask;
                break;
            case SSD1306_COLOR_INVERT:
                ctx->buffer[index] ^= mask;
                break;
        }
    }

draw_vline_finish:
    if (ctx->refresh_left > x) ctx->refresh_left = x;
    if (ctx->refresh_right < x) ctx->refresh_right = x;
    if (ctx->refresh_top > y) ctx->refresh_top = y;
    if (ctx->refresh_bottom < y + h - 1) ctx->refresh_bottom = y + h - 1;
    return;
}

void ssd1306_draw_rectangle(uint8_t id, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color){
    ssd1306_draw_hline(id, x, y, w, color);
    ssd1306_draw_hline(id, x, y + h - 1, w, color);
    ssd1306_draw_vline(id, x, y, h, color);
    ssd1306_draw_vline(id, x + w - 1, y, h, color);
}

void ssd1306_fill_rectangle(uint8_t id, int8_t x, int8_t y, uint8_t w, uint8_t h, ssd1306_color_t color){
    uint8_t i;
    for (i = x; i < x + w; ++i)
        ssd1306_draw_vline(id, i, y, h, color);
}

void ssd1306_select_font(uint8_t id, uint8_t idx){
    oled_i2c_ctx *ctx = _ctxs[id];

    if (ctx == NULL) return;

    if (idx < OLED_NUM_FONTS)
        ctx->font = oled_fonts[idx];
}

uint8_t ssd1306_measure_string(uint8_t id, char *str){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint8_t w = 0;
    unsigned char chr;

    if (ctx == NULL) return 0;

    if (ctx->font == NULL) return 0;

    while (*str)
    {
        chr = *str;
        // we always have space in the font set
        if ((chr < ctx->font->char_start) || (chr > ctx->font->char_end)) chr = ' ';

        chr = chr - ctx->font->char_start;   // c now become index to tables
        w += ctx->font->char_descriptors[chr].width;
        ++str;
        if (*str) w += ctx->font->c;
    }

    return w;
}

uint8_t ssd1306_draw_char(uint8_t id, uint8_t x, uint8_t y, unsigned char chr, ssd1306_color_t foreground, ssd1306_color_t background){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint8_t i, j;
    const uint8_t *bitmap;
    uint8_t line = 0;

    if (ctx == NULL) return 0;
    if (ctx->font == NULL) return 0;

    if ((chr < ctx->font->char_start) || (chr > ctx->font->char_end)) chr = ' ';
    chr = chr - ctx->font->char_start;
    bitmap = ctx->font->bitmap + ctx->font->char_descriptors[chr].offset;

    for (j = 0; j < ctx->font->height; ++j){
        for (i = 0; i < ctx->font->char_descriptors[chr].width; ++i){
            if (i % 8 == 0){
                line = bitmap[(ctx->font->char_descriptors[chr].width + 7) / 8 * j + i / 8];
            }

            if (line & 0x80){
                ssd1306_draw_pixel(id, x + i, y + j, foreground);
            }
            else{
                switch (background){
                    case SSD1306_COLOR_TRANSPARENT:
                        break;
                    case SSD1306_COLOR_WHITE:
                    case SSD1306_COLOR_BLACK:
                        ssd1306_draw_pixel(id, x + i, y + j, background);
                        break;
                    case SSD1306_COLOR_INVERT:
                        break;
                }
            }

            line = line << 1;
        }
    }

    return (ctx->font->char_descriptors[chr].width);
}

uint8_t ssd1306_draw_string(uint8_t id, uint8_t x, uint8_t y, char *str, ssd1306_color_t foreground, ssd1306_color_t background){
    oled_i2c_ctx *ctx = _ctxs[id];
    uint8_t t = x;

    if (ctx == NULL) return 0;
    if (ctx->font == NULL) return 0;
    if (str == NULL) return 0;

    while (*str){
        x += ssd1306_draw_char(id, x, y, *str, foreground, background);
        ++str;
        if(*str)x += ctx->font->c;
    }

    return (x-t);
}

