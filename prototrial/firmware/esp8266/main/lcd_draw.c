#include "my_includes.h"

#include "image.xbm"

#define SEC_DELAY (100 / portTICK_PERIOD_MS)

extern ssd1306_t oled_dev;

static bool imgfwd = true;
static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

void test_olcd_img(void){
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_load_xbm(&oled_dev, image_bits, lcdbuff);
}

void test_olcd_flip(void){
    ssd1306_set_scan_direction_fwd(&oled_dev, imgfwd);
    imgfwd = !imgfwd;
}

void test_olcd_text(void){
    char text[20];

    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    sprintf(text, "Hello, ESP8266-IDF");
    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[DEFAULT_FONT],
                        0, 0,
                        "Hello, ESP8266-IDF",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

static void ssd1306_task(void *pvParameters){
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000/portTICK_PERIOD_MS);


    if (ssd1306_load_xbm(&oled_dev, image_bits, lcdbuff))
        goto error_loop;

    bool fwd = false;
    while (1) {
        vTaskDelay(2*SEC_DELAY);
        printf("%s: still alive, flipping!\n", __FUNCTION__);
        ssd1306_set_scan_direction_fwd(&oled_dev, fwd);
        fwd = !fwd;
    }

error_loop:
    printf("%s: error while loading framebuffer into SSD1306\n", __func__);
    for(;;){
        vTaskDelay(2*SEC_DELAY);
        printf("%s: error loop\n", __FUNCTION__);
    }
}

void test_olcd_loop(void){
    while (ssd1306_init(&oled_dev) != 0){
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(SEC_DELAY);
    }

    vTaskDelay(SEC_DELAY);
    ssd1306_clear_screen(&oled_dev);
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));
    xTaskCreate(ssd1306_task, "ssd1306_task", 2048, NULL, 2, NULL);
}
