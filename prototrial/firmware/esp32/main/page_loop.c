#include "my_includes.h"

uint8_t pageNum = PAGE_HOME;

static void page_task_loop(void *arg){
    (void)arg;

    while(1){
        switch (pageNum) {

        case PAGE_HOME:
            page_home();
            break;

        case PAGE_FILES:
            page_files_demo();
            break;

        case PAGE_PLOT:
            page_plot_demo();
            break;

        case PAGE_SEND:
            page_send_demo();
            break;

        default:
            break;
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void start_page(void){
    start_send_page();
    xTaskCreate(page_task_loop, "page loop", 2048, NULL, tskIDLE_PRIORITY, NULL);
}
