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

#if MY_UART_NOLOG
    esp_log_level_set("*", ESP_LOG_NONE);
#else
    esp_log_level_set("*", ESP_LOG_VERBOSE);
#endif

/** must first before other module */
#if MY_USE_NVS
    my_nvsInit();
#endif

#if MY_USE_LED
    my_ledInit();
#else
    my_ledDisabled();
#endif

#if MY_USE_BTN
    my_btnInit();
#endif

#if MY_USE_ADC
    my_adcInit();
#endif

#if MY_USE_I2SMIC
    my_i2smicInit();
#endif

#if MY_USE_OLCD
    my_oledInit();
    my_olcdtest_img();

 #if MY_PAGE_HOME
    my_pageHome();
 #endif

 #if MY_PAGE_LOOP
    my_pageLoop();
 #endif
#endif

#if MY_USE_UART
    my_shellInit();
#endif

#if MY_USE_STM32
 #if MY_STM32_IOSTATUS
    msg_htiosttInit();
 #endif
#endif

#if MY_USE_WIFI
 #if MY_WIFI_ONCMD
 #else
  #if MY_WIFI_STA
    my_wifiInitSTA();
  #endif
  #if MY_WIFI_AP
    my_wifiInitAP();
  #endif
 #endif
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
