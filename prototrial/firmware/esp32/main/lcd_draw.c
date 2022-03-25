/**
 * @file lcd_draw.c
 * @brief Basic LCD Draw source
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

#include "logo.xbm"

extern ssd1306_t oled_dev;

/**
 * @brief Tag for LCD command
 *
 */
static const char *TAG = "OLED";

/**
 * @brief LCD pixel buffer array
 *
 */
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void register_oled_img();
static void register_oled_text();

/**
 * @brief register basic LCD commands
 *
 */
void register_oled(void){
    register_oled_img();
    register_oled_text();
}

/**
 * @brief Test image drawing
 *
 */
void test_olcd_img(void){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_load_xbm(&oled_dev, logo_bits, lcdbuff);
}

/**
 * @brief LCD image command
 *
 * @param argc
 * @param argv
 * @return int
 */
static int oled_img(int argc, char **argv){
    test_olcd_img();

    ESP_LOGI(TAG, "Draw test OLED LCD");
    return 0;
}

/**
 * @brief Register LCD image command
 *
 */
static void register_oled_img(){
    const esp_console_cmd_t oled_img_cmd = {
        .command = "oled-img",
        .help = "Image OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_img,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_img_cmd) );
}

/**
 * @brief LCD text command
 *
 * @param argc
 * @param argv
 * @return int
 */
static int oled_text(int argc, char **argv){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_GLCD5x7],
                        0, 0, "GLCD-5x7",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                        0, 10, "TERMINUS-6x12", // ymin = 0 + |7| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_8X14_ISO8859_1],
                        0, 25, "TERMINUSB-8x14", // ymin = 10 + |12| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_BOLD_10X18_ISO8859_1],
                        0, 42, "TERMINUSB-10x18", // ymin = 25 + |14| + 3
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);

    ESP_LOGI(TAG, "Text test OLED LCD");
    return 0;
}

/**
 * @brief Register LCD text command
 *
 */
static void register_oled_text(){
    const esp_console_cmd_t oled_text_cmd = {
        .command = "oled-text",
        .help = "Text OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_text,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_text_cmd) );
}

/** @} */
