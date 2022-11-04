/**
 * @file page_home.c
 * @brief Page Home source
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

extern ssd1306_t oled_dev;
extern uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

extern uint8_t my_wifi_type;
extern tcpip_adapter_ip_info_t ipInfo;

/**
 * @brief Progress Percent
 */
uint8_t runPercent = 0;

/**
 * @brief Battery percent
 *
 */
int battPercent = 69;

/**
 * @brief Ambient dB
 *
 */
uint16_t ambientDB = 110;

/**
 * @brief Flag STM32 run/idle/prep status
 *
 */
uint8_t runIdle = HT_STATE_PREP;

/**
 * @brief Draw Battery in Full state
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_batt_full(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,48,3,12,18,OLED_COLOR_WHITE);
}

/**
 * @brief Draw Battery in Empty state
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_batt_empty(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,48,3,12,18,OLED_COLOR_WHITE);
}

/**
 * @brief Draw Battery in Half state
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_batt_half(const ssd1306_t *dev, uint8_t *fb){
    ssd1306_fill_rectangle(dev,fb,51,0,6,2,OLED_COLOR_WHITE);
    ssd1306_draw_rectangle(dev,fb,48,3,12,9,OLED_COLOR_WHITE);
    ssd1306_fill_rectangle(dev,fb,48,11,12,9,OLED_COLOR_WHITE);
}

/**
 * @brief Draw Battery percent
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_info_batt(const ssd1306_t *dev, uint8_t *fb){
    char strBattPercent[5];

    my_adcGetBatt();

    sprintf(strBattPercent,"%3d%%",battPercent);
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

/**
 * @brief Draw Audiometri Progress Percent
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_info_progress(const ssd1306_t *dev, uint8_t *fb){
    char strPercent[10];

    sprintf(strPercent,"Run: %3i%%",runPercent);
    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        64, 3, strPercent,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);
}

/**
 * @brief Draw WIFI mode
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_info_wifimode(const ssd1306_t *dev, uint8_t *fb){
    if(my_wifi_type==WIFI_TYPE_OFF){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            64, 10, "WiFiOFF",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else if(my_wifi_type==WIFI_TYPE_AP){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            64, 10, "A-Point",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else if(my_wifi_type==WIFI_TYPE_STA){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                            64, 10, "Station",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

}

/**
 * @brief Draw STM32 run/idle status
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_info_runmode(const ssd1306_t *dev, uint8_t *fb){
    if(runIdle==HT_STATE_PREP){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                            10, 25, "PREP",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    else if(runIdle==HT_STATE_IDLE){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                            10, 25, "IDLE",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
    if(runIdle==HT_STATE_RUN){
        ssd1306_draw_string(dev,
                            fb,
                            font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_12X24_ISO8859_1],
                            10, 25, "RUN",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }
}

/**
 * @brief Draw ambient dB
 *
 * @param dev LCD device object
 * @param fb frame buffer array
 */
static void page_info_ambient(const ssd1306_t *dev, uint8_t *fb){
    char strAmbientDB[8];

    if(ambientDB <= 999){
        sprintf(strAmbientDB, "%3idB", ambientDB);
    }
    else{
        sprintf(strAmbientDB, "999dB");
    }
    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_TERMINUS_8X14_ISO8859_1],
                        75, 28, strAmbientDB,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);
}

static void page_info_ip(const ssd1306_t *dev, uint8_t *fb){
    char strIP[30];

    sprintf(strIP,"IP: %s",ip4addr_ntoa(&ipInfo.ip));
    ssd1306_draw_string(dev,
                        fb,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 50, strIP,
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);
}

/**
 * @brief Draw Page Home
 *
 */
void my_pageHome(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    page_info_batt(&oled_dev,lcdbuff);
    page_info_progress(&oled_dev,lcdbuff);
    page_info_wifimode(&oled_dev,lcdbuff);
    page_info_runmode(&oled_dev,lcdbuff);
    page_info_ambient(&oled_dev, lcdbuff);
    page_info_ip(&oled_dev,lcdbuff);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

/** @} */
