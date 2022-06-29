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

#if MY_UART_SILENT
    esp_log_level_set("*", ESP_LOG_NONE);
#endif

/** must first before other module */
#if MY_USE_NVS
    my_nvsInit();
#endif

#if MY_USE_LED
    my_ledInit();
#endif

#if MY_USE_UART
    my_shellInit();
#endif

    while(1) {
#if MY_USE_UART
 #if MY_UART_DUMB
  my_shellLoop();
 #else
  int shloop = my_shellLoop();
  if(shloop==1)("Empty Command\r\n");
 #endif
#endif

    }
}

/** @} */