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

#if MY_USE_WIFI
 #if MY_WIFI_STA
    my_wifiInitSTA();
 #endif
 #if MY_WIFI_AP
    my_wifiInitAP();
 #endif
#endif

#if MY_USE_OLCD
    my_oledInit();
    my_olcdtest_img();
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
