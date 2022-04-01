/**
 * @file    main.c
 * @brief   Main entry program code.
 *
 * @addtogroup Main
 * @{
 */

#include "my_includes.h"

extern uint8_t runIdle;

/**
 * @brief Main entry function
 * @details First main function app
 */
void app_main(void){

#if UART_TO_STM32
    esp_log_level_set("*", ESP_LOG_NONE);
#endif

    nvsInit();
    start_ssd1306();
    shellInit();
    // start_wifiAP();
    start_wifiSTA();
    start_page();
    start_i2smic();
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
