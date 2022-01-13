/**
 * Original works:
 * https://github.com/Fonger/ESP8266-RTOS-SSD1306/blob/master/ssd1306/ssd1306.c
 */

#include "my_includes.h"

#ifdef SSD1306_DEBUG
 #define debug(fmt, ...) printf("%s: " fmt "\n", "SSD1306", ## __VA_ARGS__)
#else
 #define debug(fmt, ...)
#endif

#define abs(x) ((x)<0 ? -(x) : (x))
#define swap(x, y) do { typeof(x) temp##x##y = x; x = y; y = temp##x##y; } while (0)

static void i2c_master_init(void){
    int i2c_master_port = I2C_NUM_0;

    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = SDA_PIN;
    conf.sda_pullup_en = 1;
    conf.scl_io_num = SCL_PIN;
    conf.scl_pullup_en = 1;
    conf.clk_stretch_tick = 300;

    ESP_ERROR_CHECK(i2c_driver_install(i2c_master_port, conf.mode));
    ESP_ERROR_CHECK(i2c_param_config(i2c_master_port, &conf));
}

static int inline i2c_send(const ssd1306_t *dev, uint8_t reg, uint8_t* data, uint8_t len){
    int ret;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);

    i2c_master_write_byte(cmd, dev->i2c_addr << 1 | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_write(cmd, data, len, true);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(dev->i2c_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

int ssd1306_command(const ssd1306_t *dev, uint8_t cmd){
    return i2c_send(dev, 0x00, &cmd, 1);
}

int ssd1306_init(const ssd1306_t *dev){
    uint8_t pin_cfg;
    switch (dev->height) {
        case 16:
            pin_cfg = 0x02;
            break;
        case 32:
            if(dev->width == 128)
                pin_cfg = 0x02;
            else
                pin_cfg = 0x12;
            break;
        case 64:
            pin_cfg = 0x12;
            break;
        default:
            debug("Unsupported screen height");
            return -ENOTSUP;
    }

    switch (dev->screen){
        case SSD1306_SCREEN:
            if (!ssd1306_display_on(dev, false)                                  &&
                !ssd1306_set_osc_freq(dev, 0x80)                                 &&
                !ssd1306_set_mux_ratio(dev, dev->height - 1)                     &&
                !ssd1306_set_display_offset(dev, 0x0)                            &&
                !ssd1306_set_display_start_line(dev, 0x0)                        &&
                !ssd1306_set_charge_pump_enabled(dev, true)                      &&
                !ssd1306_set_mem_addr_mode(dev, SSD1306_ADDR_MODE_HORIZONTAL)    &&
                !ssd1306_set_segment_remapping_enabled(dev, false)               &&
                !ssd1306_set_scan_direction_fwd(dev, true)                       &&
                !ssd1306_set_com_pin_hw_config(dev, pin_cfg)                     &&
                !ssd1306_set_contrast(dev, 0x9f)                                 &&
                !ssd1306_set_precharge_period(dev, 0xf1)                         &&
                !ssd1306_set_deseltct_lvl(dev, 0x40)                             &&
                !ssd1306_set_whole_display_lighting(dev, true)                   &&
                !ssd1306_set_inversion(dev, false)                               &&
                !ssd1306_display_on(dev, true)) {
                return 0;
            }
            break;
        case SH1106_SCREEN:
            if (!ssd1306_display_on(dev, false)                                  &&
                !ssd1306_set_charge_pump_enabled(dev, true)                      &&
                !sh1106_set_charge_pump_voltage(dev,SH1106_VOLTAGE_74)           &&
                !ssd1306_set_osc_freq(dev, 0x80)                                 &&
                !ssd1306_set_mux_ratio(dev, dev->height - 1)                     &&
                !ssd1306_set_display_offset(dev, 0x0)                            &&
                !ssd1306_set_display_start_line(dev, 0x0)                        &&
                !ssd1306_set_segment_remapping_enabled(dev, true)                &&
                !ssd1306_set_scan_direction_fwd(dev, true)                       &&
                !ssd1306_set_com_pin_hw_config(dev, pin_cfg)                     &&
                !ssd1306_set_contrast(dev, 0x9f)                                 &&
                !ssd1306_set_precharge_period(dev, 0xf1)                         &&
                !ssd1306_set_deseltct_lvl(dev, 0x40)                             &&
                !ssd1306_set_whole_display_lighting(dev, true)                   &&
                !ssd1306_set_inversion(dev, false)                               &&
                !ssd1306_display_on(dev, true)) {
                return 0;
            }
            break;
    }
    return -EIO;
}

int ssd1306_display_on(const ssd1306_t *dev, bool on){
    return ssd1306_command(dev, on ? SSD1306_SET_DISPLAY_ON : SSD1306_SET_DISPLAY_OFF);
}

int ssd1306_set_osc_freq(const ssd1306_t *dev, uint8_t osc_freq){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_OSC_FREQ))) return err;

    return ssd1306_command(dev, osc_freq);
}

int ssd1306_set_mux_ratio(const ssd1306_t *dev, uint8_t ratio){
    if ((ratio < 15) || (ratio > 63)) return -EINVAL;

    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_MUX_RATIO))) return err;

    return ssd1306_command(dev, ratio);
}

int ssd1306_set_display_offset(const ssd1306_t *dev, uint8_t offset)
{
    if (offset > 63) return -EINVAL;

    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_DISPLAY_OFFSET))) return err;

    return ssd1306_command(dev, offset);
}

int ssd1306_set_display_start_line(const ssd1306_t *dev, uint8_t start){
    if (start > 63) return -EINVAL;

    return ssd1306_command(dev, SSD1306_SET_DISP_START_LINE | start);
}

int ssd1306_set_charge_pump_enabled(const ssd1306_t *dev, bool enabled){
    int err = 0;
    switch (dev->screen) {
        case SH1106_SCREEN:
            if ((err = ssd1306_command(dev, SH1106_SET_CHARGE_PUMP))) return err;
            return ssd1306_command(dev, enabled ? SH1106_CHARGE_PUMP_EN : SH1106_CHARGE_PUMP_DIS);
            break;
        case SSD1306_SCREEN:
            if ((err = ssd1306_command(dev, SSD1306_SET_CHARGE_PUMP))) return err;
            return ssd1306_command(dev, enabled ? SSD1306_CHARGE_PUMP_EN : SSD1306_CHARGE_PUMP_DIS);
            break;
        default:
            debug("Unsupported screen type");
            return -ENOTSUP;
    }
}

int sh1106_set_charge_pump_voltage(const ssd1306_t *dev, sh1106_voltage_t select){
    if (dev->screen == SSD1306_SCREEN) {
        debug("Unsupported screen type");
        return -ENOTSUP;
    }

    return ssd1306_command(dev, select | SH1106_CHARGE_PUMP_VALUE);
}

int ssd1306_set_deseltct_lvl(const ssd1306_t *dev, uint8_t lvl){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_DESEL_LVL))) return err;

    return ssd1306_command(dev, lvl);
}

int ssd1306_set_mem_addr_mode(const ssd1306_t *dev, ssd1306_mem_addr_mode_t mode){
    if (dev->screen == SH1106_SCREEN) {
        debug("Unsupported screen type");
        return -ENOTSUP;
    }

    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_MEM_ADDR_MODE))) return err;

    return ssd1306_command(dev, mode);
}

int ssd1306_set_segment_remapping_enabled(const ssd1306_t *dev, bool on){
    return ssd1306_command(dev, on ? SSD1306_SET_SEGMENT_REMAP1 : SSD1306_SET_SEGMENT_REMAP0);
}

int ssd1306_set_scan_direction_fwd(const ssd1306_t *dev, bool fwd){
    return ssd1306_command(dev, fwd ? SSD1306_SET_SCAN_DIR_FWD : SSD1306_SET_SCAN_DIR_BWD);
}


int ssd1306_set_com_pin_hw_config(const ssd1306_t *dev, uint8_t config){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_COM_PINS_HW_CFG))) return err;

    return ssd1306_command(dev, config & SSD1306_COM_PINS_HW_CFG_MASK);
}

int ssd1306_set_contrast(const ssd1306_t *dev, uint8_t contrast){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_CONTRAST))) return err;

    return ssd1306_command(dev, contrast);
}

int ssd1306_set_precharge_period(const ssd1306_t *dev, uint8_t prchrg){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_PRE_CHRG_PER))) return err;

    return ssd1306_command(dev, prchrg);
}

int ssd1306_set_whole_display_lighting(const ssd1306_t *dev, bool light){
    return ssd1306_command(dev, light ? SSD1306_SET_ENTIRE_DISP_ON : SSD1306_SET_ENTIRE_DISP_OFF);
}

int ssd1306_set_inversion(const ssd1306_t *dev, bool on){
    return ssd1306_command(dev, on ? SSD1306_SET_INVERSION_ON : SSD1306_SET_INVERSION_OFF);
}

static int sh1106_go_coordinate(const ssd1306_t *dev, uint8_t x, uint8_t y){
    if (x >= dev->width || y >= (dev->height / 8)) return -EINVAL;
    int err = 0;

    x += 2; //offset : panel is 128 ; RAM is 132 for sh1106
    if ((err = ssd1306_command(dev, SH1106_SET_PAGE_ADDRESS + y))) // Set row
        return err;
    if ((err = ssd1306_command(dev, SH1106_SET_LOW_COL_ADDR | (x & 0xf))))  // Set lower column address
        return err;

    return ssd1306_command(dev, SH1106_SET_HIGH_COL_ADDR | (x >> 4)); //Set higher column address
}

int ssd1306_set_column_addr(const ssd1306_t *dev, uint8_t start, uint8_t stop){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_COL_ADDR)))
        return err;

    if ((err = ssd1306_command(dev, start)))
        return err;

    return ssd1306_command(dev, stop);
}

int ssd1306_set_page_addr(const ssd1306_t *dev, uint8_t start, uint8_t stop){
    int err = 0;
    if ((err = ssd1306_command(dev, SSD1306_SET_PAGE_ADDR)))
        return err;

    if ((err = ssd1306_command(dev, start)))
        return err;

    return ssd1306_command(dev, stop);
}

int ssd1306_load_frame_buffer(const ssd1306_t *dev, uint8_t buf[])
{
    uint16_t i;
    uint8_t tab[16] = { 0 };
    size_t len = dev->width * dev->height / 8;
    if (dev->screen == SSD1306_SCREEN) {
        if(dev->width == 64 && dev->height == 32) {
            ssd1306_set_column_addr(dev, 0x20, 0x20 + (dev->width - 1));
        } else {
            ssd1306_set_column_addr(dev, 0, dev->width - 1);
        }
        ssd1306_set_page_addr(dev, 0, dev->height / 8 - 1);
    }

    for (i = 0; i < len; i++) {
        if (dev->screen == SH1106_SCREEN && i % dev->width == 0)
            sh1106_go_coordinate(dev, 0, i / dev->width);
        i2c_send(dev, 0x40, buf ? &buf[i] : tab, 16);
        i += 15;
    }

    return 0;
}

int ssd1306_load_xbm(const ssd1306_t *dev, uint8_t *xbm, uint8_t *fb){
    uint8_t bit = 0;

    int row = 0;
    int column = 0;
    for (row = 0; row < dev->height; row++) {
        for (column = 0; column < dev->width / 8; column++) {
            uint16_t xbm_offset = row * 16 + column;
            for (bit = 0; bit < 8; bit++) {
                if (*(xbm + xbm_offset) & 1 << bit) {
                    *(fb + dev->width * (row / 8) + column * 8 + bit) |= 1 << row % 8;
                }
            }
        }
    }

    return ssd1306_load_frame_buffer(dev, fb);
}

int ssd1306_clear_screen(const ssd1306_t *dev){
    return ssd1306_load_frame_buffer(dev, NULL);
}

void start_ssd1306(void){
    int i2c_master_port = I2C_NUM_0;
    i2c_master_init();

    ssd1306_t dev = {
            .i2c_port = i2c_master_port,
            .i2c_addr = SSD1306_I2C_ADDR,
            .screen = SSD1306_SCREEN, // or SH1106_SCREEN
            .width = DISPLAY_WIDTH,
            .height = DISPLAY_HEIGHT
    };

    ssd1306_init(&dev);
    ssd1306_clear_screen(&dev);
}
