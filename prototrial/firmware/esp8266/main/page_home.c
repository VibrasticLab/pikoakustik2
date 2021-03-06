#include "my_includes.h"

extern ssd1306_t oled_dev;
extern tcpip_adapter_ip_info_t ipInfo;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];
static uint8_t battPercent = 69;
\
bool runIdle = true;
extern bool wifi_ap;

static void page_batt_full(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,48,3,12,18,OLED_COLOR_WHITE);
}

static void page_batt_empty(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,48,3,12,18,OLED_COLOR_WHITE);
}

static void page_batt_half(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,48,3,12,9,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,48,11,12,9,OLED_COLOR_WHITE);
}

static void page_info_batt(const ssd1306_t *dev, uint8_t *fb){
    char strBattPercent[5];

    sprintf(strBattPercent,"%3i%%",battPercent);
    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_TERMINUS_12X24_ISO8859_1],
                        0, 0, strBattPercent,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    if(battPercent>=70){
        page_batt_full(dev,fb);
    }
    else if((battPercent<70) && (battPercent>=40)){
        page_batt_half(dev,fb);
    }
    else if(battPercent<40){
        page_batt_empty(dev,fb);
    }
}

static void page_info_wifimode(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        64, 3, "WiFi Mode:",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    if(wifi_ap){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            64, 10, "A-Point",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else{
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            64, 10, "Station",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

}

static void page_info_runmode(const ssd1306_t *dev, uint8_t *fb){
    if(runIdle){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                            32, 25, "IDLE",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else{
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                            32, 25, "RUN",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
}

static void page_info_ip(const ssd1306_t *dev, uint8_t *fb){
    char strIP[30];

    sprintf(strIP,"IP: %s",ip4addr_ntoa(&ipInfo.ip));
    if(strlen(strIP)>0){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_GLCD5x7],
                            0, 50, strIP,
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else{
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_GLCD5x7],
                            0, 50, "IP: unavailable",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
}

void page_home(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    page_info_batt(&oled_dev,lcdbuff);
    page_info_wifimode(&oled_dev,lcdbuff);
    page_info_runmode(&oled_dev,lcdbuff);
    page_info_ip(&oled_dev,lcdbuff);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}
