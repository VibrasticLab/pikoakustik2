/**
 * @file my_cmd.c
 * @brief Console commands source
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

extern uint16_t led_delay;
extern uint8_t pageNum;
extern uint8_t my_wifi_type;
extern uint8_t runPercent;

static void register_version(void);
static void register_restart(void);
static void register_pagehome(void);
static void register_leddelay(void);
static void register_adctest(void);
static void register_wifion(void);
static void register_audpercent(void);
static void register_jsonpta(void);

void my_registerCommands(void)
{
    register_version();
    register_restart();
    register_pagehome();
    register_leddelay();
    register_adctest();
    register_wifion();
    register_audpercent();
    register_jsonpta();
}

/**
 * @brief Get the system version
 *
 * @param argc
 * @param argv
 * @return int
 */
static int get_version(int argc, char **argv)
{
    esp_chip_info_t info;

    esp_chip_info(&info);
    printf("IDF Version:%d.%d.%d\r\n",ESP_IDF_VERSION_MAJOR,ESP_IDF_VERSION_MINOR,ESP_IDF_VERSION_PATCH);
    printf("Chip info:\r\n");
    printf("\tmodel:%s\r\n", info.model == CHIP_ESP32 ? "ESP32" : "Unknow");
    printf("\tcores:%d\r\n", info.cores);
    printf("\tfeature:%s%s%s%s%d%s\r\n",
           info.features & CHIP_FEATURE_WIFI_BGN ? "/802.11bgn" : "",
           info.features & CHIP_FEATURE_BLE ? "/BLE" : "",
           info.features & CHIP_FEATURE_BT ? "/BT" : "",
           info.features & CHIP_FEATURE_EMB_FLASH ? "/Embedded-Flash:" : "/External-Flash:",
           spi_flash_get_chip_size() / (1024 * 1024), " MB");
    printf("\trevision number:%d\r\n", info.revision);
    return 0;
}

/**
 * @brief Register system version command
 *
 */
static void register_version(void)
{
    const esp_console_cmd_t cmd = {
        .command = "ver",
        .help = "Get version of chip and SDK",
        .hint = NULL,
        .func = &get_version,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Restart system
 *
 * @param argc
 * @param argv
 * @return int
 */
static int restart(int argc, char **argv)
{
    printf("Restarting\r\n");
    esp_restart();
}

/**
 * @brief Register restart system command
 *
 */
static void register_restart(void)
{
    const esp_console_cmd_t cmd = {
        .command = "rst",
        .help = "Software reset of the chip",
        .hint = NULL,
        .func = &restart,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Go Page Home
 *
 * @param argc
 * @param argv
 * @return int
 */
static int gopagehome(int argc, char **argv)
{
    pageNum = PAGE_HOME;
    return 0;
}

/**
 * @brief Register Go Page Home command
 *
 */
static void register_pagehome(void)
{
    const esp_console_cmd_t cmd = {
        .command = "home",
        .help = "Go Page Home",
        .hint = NULL,
        .func = &gopagehome,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Set the LED Delay
 *
 * @param argc
 * @param argv
 * @return int
 */
static int set_leddelay(int argc, char **argv)
{
#if MY_USE_LED
    if(argc==2){
        led_delay = atoi(argv[1]);
        if(led_delay<=20) led_delay = 20;

 #if MY_UART_SILENT
 #else
        printf("led delay %i\n",led_delay);
 #endif
    }
#endif

    return 0;
}

/**
 * @brief Register led delay command
 *
 */
static void register_leddelay(void)
{
    const esp_console_cmd_t cmd = {
        .command = "led",
        .help = "Set LED Delay: led <delay in ms>",
        .hint = NULL,
        .func = &set_leddelay,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Get Single ADC value
 *
 * @param argc
 * @param argv
 * @return int
 */
static int adctest(int argc, char **argv)
{
#if MY_USE_ADC
   my_adcValue();
#endif

   return 0;
}

/**
 * @brief Register Get ADC command
 *
 */
static void register_adctest(void)
{
    const esp_console_cmd_t cmd = {
        .command = "adc",
        .help = "Get single ADC value",
        .hint = NULL,
        .func = &adctest,
    };
    esp_console_cmd_register(&cmd);
}
/**
 * @brief Activate the Wifi
 *
 * @param argc
 * @param argv
 * @return int
 */
static int wifion(int argc, char **argv)
{
    uint8_t wifi_flag = 0;

    if(argc==2){
        wifi_flag = atoi(argv[1]);

        if(wifi_flag==1){
            printf("Activating WiFi\r\n");
#if MY_WIFI_ONCMD
 #if MY_WIFI_STA
            if(my_wifi_type!=WIFI_TYPE_STA) my_wifiInitSTA();
 #endif
 #if MY_WIFI_AP
            if(my_wifi_type!=WIFI_TYPE_AP) my_wifiInitAP();
 #endif
#else
            printf("WiFi activated at startup\r\n");
#endif
        }
        else{
#if MY_WIFI_ONCMD
            printf("Deactivating WiFi\r\n");
            my_httpdStop();
            ESP_ERROR_CHECK(esp_wifi_stop() );

#else
            printf("WiFi always activated at startup\r\n");
#endif
        }
    }
    return 0;
}

/**
 * @brief Activate the Wifi command
 *
 */
static void register_wifion(void)
{
    const esp_console_cmd_t cmd = {
        .command = "wifi",
        .help = "Activate the WiFi",
        .hint = NULL,
        .func = &wifion,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Set the Audiometri Progress Percent
 *
 * @param argc
 * @param argv
 * @return int
 */
static int set_audpercent(int argc, char **argv)
{
    uint8_t audPercent;

    audPercent = atoi(argv[1]);
    if(audPercent<=0) {runPercent=0;}
    else if(audPercent>=100) {runPercent=100;}
    else{runPercent=audPercent;}

    return 0;
}

/**
 * @brief Register the Audiometri Progress command
 *
 */
static void register_audpercent(void)
{
    const esp_console_cmd_t cmd = {
        .command = "aud",
        .help = "Set Audiometri Progress: aud <percent>",
        .hint = NULL,
        .func = &set_audpercent,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief get the Audiometri JSON PTA into PTA Array
 *
 * @param argc
 * @param argv
 * @return int
 */
static int get_ptajson(int argc, char **argv)
{
    if(argc!=2) return 0;

    char *ptacsv = argv[1];
    my_ptaArrayLoad(ptacsv);

    return 0;
}

/**
 * @brief Register the Audiometri PTA JSON command
 *
 */
static void register_jsonpta(void){
    const esp_console_cmd_t cmd = {
        .command = "mpta",
        .help = "get Audiometri PTA JSON: mpta <json_string>",
        .hint = NULL,
        .func = &get_ptajson,
    };
    esp_console_cmd_register(&cmd);
}

/** @} */
