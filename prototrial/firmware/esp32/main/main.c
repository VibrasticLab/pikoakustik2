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
    shellInit();
    start_wifiAP();
    start_page();
    start_mic();
    start_exti();
    ledInit();

    while(1){
#ifdef CONSOLE_DUMB
        shellLoop();
#else
        int loop = shellLoop();
        if(loop==1)printf("Empty Command\r\n");
#endif
    }
}

/** @} */
