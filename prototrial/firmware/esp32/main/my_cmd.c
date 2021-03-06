/**
 * @file my_cmd.c
 * @brief Console commands source
 *
 * @addtogroup Console
 * @{
 */

/* Console example — various system commands

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "my_includes.h"

extern uint8_t pageNum;
extern bool pageSWable;

static void register_version(void);
static void register_restart(void);
static void register_pageloop(void);

/**
 * @brief Register all basic commands
 *
 */
void registerCommands(void)
{
    register_version();
    register_restart();
    register_pageloop();
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
        .command = "sys-version",
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
        .command = "sys-restart",
        .help = "Software reset of the chip",
        .hint = NULL,
        .func = &restart,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief LCD switch page
 *
 * @param argc
 * @param argv
 * @return int
 */
static int func_pageloop(int argc, char **argv){
    if(pageSWable){
        if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
        else{pageNum++;}
    }

    return 0;
}

/**
 * @brief Register LCD switch page command
 *
 */
static void register_pageloop(void){
    const esp_console_cmd_t cmd_pageloop = {
        .command = "page",
        .help = "Display Page Loop",
        .hint = NULL,
        .func = &func_pageloop,
    };

    esp_console_cmd_register(&cmd_pageloop);
}

/** @} */
