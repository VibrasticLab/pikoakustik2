#include "my_includes.h"

uint8_t pageNum = PAGE_HOME;

static void page_task_loop(void *arg){
    while(1){
        switch (pageNum) {
        case PAGE_HOME:
            page_home();
            break;
        default:
            break;
        }

        vTaskDelay(500 / portTICK_RATE_MS);
    }
}

void start_page(void){
    xTaskCreate(page_task_loop, "page loop", 2048, NULL, 2, NULL);
}
