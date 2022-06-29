/**
 * @file    main.c
 * @brief   Main entry program code.
 *
 * @addtogroup Main
 * @{
 */

#include "my_includes.h"

/**
 * @brief Main entry function
 * @details First main function app
 */
void app_main(void){

#if MY_USE_LED
    my_ledInit();
#endif

    while(1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/** @} */