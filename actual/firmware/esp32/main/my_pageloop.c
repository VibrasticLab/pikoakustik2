/**
 * @file my_pageloop.c
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
#if MY_PAGE_HOME
            my_pageHome();
#endif
            break;

        case PAGE_FILES:
#if MY_PAGE_FILES
            page_files_demo();
#endif
            break;

        case PAGE_PLOT:
#if MY_PAGE_PLOT
            page_plot_demo();
#endif
            break;

        case PAGE_SEND:
#if MY_PAGE_SEND
            page_send();
#endif
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
void my_pageLoop(void){
    xTaskCreate(page_task_loop, "page_page", 4096 + 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */
