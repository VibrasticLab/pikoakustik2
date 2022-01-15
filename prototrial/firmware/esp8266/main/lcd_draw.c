#include "my_includes.h"

#include "logo.xbm"

extern ssd1306_t oled_dev;

static const char *TAG = "cmd_oled";

static bool imgfwd = true;
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void register_oled_img();
static void register_oled_flip();
static void register_oled_text();

void register_oled(void){
    register_oled_img();
    register_oled_flip();
    register_oled_text();
}

void test_olcd_img(void){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_load_xbm(&oled_dev, logo_bits, lcdbuff);
}

void test_olcd_flip(void){
    ssd1306_set_scan_direction_fwd(&oled_dev, imgfwd);
    imgfwd = !imgfwd;
}

void test_olcd_text(void){
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
}

static void ssd1306_task(void *pvParameters){
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000 / portTICK_RATE_MS);


    if (ssd1306_load_xbm(&oled_dev, logo_bits, lcdbuff))
        goto error_loop;

    bool fwd = false;
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("%s: still alive, flipping!\n", __FUNCTION__);
        ssd1306_set_scan_direction_fwd(&oled_dev, fwd);
        fwd = !fwd;
    }

error_loop:
    printf("%s: error while loading framebuffer into SSD1306\n", __func__);
    for(;;){
        vTaskDelay(1000 / portTICK_RATE_MS);
        printf("%s: error loop\n", __FUNCTION__);
    }
}

void test_olcd_loop(void){
    while (ssd1306_init(&oled_dev) != 0){
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }

    vTaskDelay(1000 / portTICK_RATE_MS);
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    xTaskCreate(ssd1306_task, "ssd1306_task", 2048, NULL, 2, NULL);
}

static int oled_img(int argc, char **argv){
    test_olcd_img();
    ESP_LOGI(TAG, "Draw test OLED LCD");
    return 0;
}

static void register_oled_img(){
    const esp_console_cmd_t oled_img_cmd = {
        .command = "oled",
        .help = "Image OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_img,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_img_cmd) );
}

static int oled_flip(int argc, char **argv){
    test_olcd_flip();
    ESP_LOGI(TAG, "flipping OLED LCD");
    return 0;
}

static void register_oled_flip(){
    const esp_console_cmd_t oled_flip_cmd = {
        .command = "flip",
        .help = "Flipping OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_flip,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_flip_cmd) );
}

static int oled_text(int argc, char **argv){
    test_olcd_text();
    ESP_LOGI(TAG, "Text test OLED LCD");
    return 0;
}

static void register_oled_text(){
    const esp_console_cmd_t oled_text_cmd = {
        .command = "text",
        .help = "Text OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_text,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_text_cmd) );
}
