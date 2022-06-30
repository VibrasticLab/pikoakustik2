/**
 * @file my_cmd.c
 * @brief Console commands source
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

extern uint16_t led_delay;

static void register_version(void);
static void register_restart(void);
static void register_leddelay(void);

void my_registerCommands(void)
{
    register_version();
    register_restart();
    register_leddelay();
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
    printf("IDF Version:%s\r\n", esp_get_idf_version());
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
    printf("Restarting");
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
 * @brief Set the LED Delay
 *
 * @param argc
 * @param argv
 * @return int
 */
static int set_leddelay(int argc, char **argv)
{
    if(argc==2){
        led_delay = atoi(argv[1]);
        if(led_delay<=20) led_delay = 20;

#if MY_UART_SILENT
#else
        printf("led delay %i\n",led_delay);
#endif
    }
    return 0;
}

/**
 * @brief Register system version command
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

/** @} */
