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

static void register_free(void);
static void register_heap(void);
static void register_version(void);
static void register_restart(void);
static void register_pageloop(void);

/**
 * @brief Register all basic commands
 *
 */
void registerCommands(void)
{
    register_free();
    register_heap();
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
        .command = "version",
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
        .command = "restart",
        .help = "Software reset of the chip",
        .hint = NULL,
        .func = &restart,
    };
    esp_console_cmd_register(&cmd);
}


/**
 * @brief Print available memory heap
 *
 * @param argc
 * @param argv
 * @return int
 */
static int free_mem(int argc, char **argv)
{
    printf("%d\n", esp_get_free_heap_size());
    return 0;
}

/**
 * @brief Register memory free command
 *
 */
static void register_free(void)
{
    const esp_console_cmd_t cmd = {
        .command = "free",
        .help = "Get the current size of free heap memory",
        .hint = NULL,
        .func = &free_mem,
    };
    esp_console_cmd_register(&cmd);
}

/**
 * @brief Print minimum heap size
 *
 * @param argc
 * @param argv
 * @return int
 */
static int heap_size(int argc, char **argv)
{
    uint32_t heapSize = heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT);
    printf("min heap size: %u\n", heapSize);
    return 0;
}

/**
 * @brief Register heap size command
 *
 */
static void register_heap(void)
{
    const esp_console_cmd_t heap_cmd = {
        .command = "heap",
        .help = "Get minimum size of free heap memory that was available during program execution",
        .hint = NULL,
        .func = &heap_size,
    };
    esp_console_cmd_register(&heap_cmd);
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
