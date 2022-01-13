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

    ctx = malloc(sizeof(oled_i2c_ctx));
    if (ctx == NULL){
        printf("Alloc OLED context failed\r\n");
        goto oled_init_fail;
    }

    if (id == 0){
#if (PANEL0_TYPE != 0)
 #if (PANEL0_TYPE == SSD1306_128x64)
        ctx->type = SSD1306_128x64;
        ctx->buffer = malloc(1024);
        ctx->width = 128;
        ctx->height = 64;
 #elif (PANEL0_TYPE == SSD1306_128x32)
        ctx->type = SSD1306_128x32;
        ctx->buffer = malloc(512);
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

    ssd1306_clear(id);
    ssd1306_refresh(id, true);

    _command(ctx->address, 0xaf);

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

