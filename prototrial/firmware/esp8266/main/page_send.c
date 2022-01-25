#include "my_includes.h"

extern ssd1306_t oled_dev;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

extern uint8_t pageNum;
extern bool pageSWable;

uint8_t sendStep = PAGE_SEND_MAX;

static void page_task_send_demo(void *arg){
    (void) arg;

    while(true){
        if(sendStep<PAGE_SEND_MAX){
            sendStep++;

            if(sendStep==PAGE_SEND_MAX){
                pageNum = PAGE_HOME;
                pageSWable = true;
            }
        }

        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void page_send(void){}

void page_send_demo(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    ssd1306_draw_string(&oled_dev,
                        lcdbuff,
                        font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                        0, 0, "Preparing sending",
                        OLED_COLOR_WHITE,
                        OLED_COLOR_BLACK);

    if(sendStep>=1){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 12, "Trying to send",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    if(sendStep>=2){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 24, "Waiting Response",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    if(sendStep>=3){
        ssd1306_draw_string(&oled_dev,
                            lcdbuff,
                            font_builtin_fonts[FONT_FACE_TERMINUS_6X12_ISO8859_1],
                            0, 36, "Completing",
                            OLED_COLOR_WHITE,
                            OLED_COLOR_BLACK);
    }

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}

void start_send_page(void){
    xTaskCreate(page_task_send_demo, "page send demo", 512, NULL, tskIDLE_PRIORITY, NULL);
}
