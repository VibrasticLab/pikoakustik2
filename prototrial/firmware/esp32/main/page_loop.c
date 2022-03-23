/**
 * @file page_loop.c
 * @brief Page Loop source
 *
 * @addtogroup LCD
 * @{
 */

#include "my_includes.h"

/**
 * @brief Page index number variable
 *
 */
uint8_t pageNum = PAGE_HOME;

/**
 * @brief Page Loop routine
 *
 * @param arg
 */
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
            page_send();
            break;

        default:
            break;
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

/**
 * @brief Start Page Loop routine
 *
 */
void start_page(void){
    xTaskCreate(page_task_loop, "page loop", 4096, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */