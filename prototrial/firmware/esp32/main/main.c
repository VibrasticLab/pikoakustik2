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
    nvsInit();
    start_ssd1306();
    test_olcd_img();
    shellInit();
    ledInit();

    while(1){
        int loop = shellLoop();
        if(loop==1)break;
    }
}

/** @} */
