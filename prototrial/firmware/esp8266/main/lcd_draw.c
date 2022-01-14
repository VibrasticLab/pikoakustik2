#include "my_includes.h"

#include "image.xbm"

#define DEFAULT_FONT FONT_FACE_GLCD5x7

extern ssd1306_t oled_dev;

#define SECOND (1000 / portTICK_PERIOD_MS)

static bool imgfwd = false;
static uint8_t buffer[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static void ssd1306_task(void *pvParameters)
{
    printf("%s: Started user interface task\n", __FUNCTION__);
    vTaskDelay(1000/portTICK_PERIOD_MS);


    if (ssd1306_load_xbm(&oled_dev, image_bits, buffer))
        goto error_loop;

    ssd1306_set_whole_display_lighting(&oled_dev, false);
    bool fwd = false;
    while (1) {
        vTaskDelay(2*SECOND);
        printf("%s: still alive, flipping!\n", __FUNCTION__);
        ssd1306_set_scan_direction_fwd(&oled_dev, fwd);
        fwd = !fwd;
    }

error_loop:
    printf("%s: error while loading framebuffer into SSD1306\n", __func__);
    for(;;){
        vTaskDelay(2*SECOND);
        printf("%s: error loop\n", __FUNCTION__);
    }
}

void test_olcd(void){
    ssd1306_load_xbm(&oled_dev, image_bits, buffer);
    ssd1306_set_whole_display_lighting(&oled_dev, false);
    ssd1306_set_scan_direction_fwd(&oled_dev, imgfwd);
}

void test_olcd_flip(void){
    ssd1306_set_scan_direction_fwd(&oled_dev, imgfwd);
    imgfwd = !imgfwd;
}

void test_olcd_loop(void){
    while (ssd1306_init(&oled_dev) != 0){
        printf("%s: failed to init SSD1306 lcd\n", __func__);
        vTaskDelay(SECOND);
    }

    ssd1306_set_whole_display_lighting(&oled_dev, true);
    vTaskDelay(SECOND);
    xTaskCreate(ssd1306_task, "ssd1306_task", 2048, NULL, 2, NULL);
}
