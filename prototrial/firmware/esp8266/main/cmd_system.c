/* Console example — various system commands

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "my_includes.h"

static const char *TAG = "cmd_system";

static void register_free();
static void register_heap();
static void register_version();
static void register_restart();
static void register_oled_img();
static void register_oled_flip();
static void register_oled_text();

void register_system(){
    register_free();
    register_heap();
    register_version();
    register_restart();
    register_oled_img();
    register_oled_flip();
    register_oled_text();
}

/* 'version' command */
static int get_version(int argc, char **argv)
{
    esp_chip_info_t info;

    esp_chip_info(&info);
    printf("IDF Version:%s\r\n", esp_get_idf_version());
    printf("Chip info:\r\n");
    printf("\tmodel:%s\r\n", info.model == CHIP_ESP8266 ? "ESP8266" : "Unknow");
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

static void register_version()
{
    const esp_console_cmd_t cmd = {
        .command = "version",
        .help = "Get version of chip and SDK",
        .hint = NULL,
        .func = &get_version,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

/** 'restart' command restarts the program */

static int restart(int argc, char **argv)
{
    ESP_LOGI(TAG, "Restarting");
    esp_restart();
}

static void register_restart()
{
    const esp_console_cmd_t cmd = {
        .command = "restart",
        .help = "Software reset of the chip",
        .hint = NULL,
        .func = &restart,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

/** 'free' command prints available heap memory */

static int free_mem(int argc, char **argv)
{
    printf("%d\n", esp_get_free_heap_size());
    return 0;
}

static void register_free()
{
    const esp_console_cmd_t cmd = {
        .command = "free",
        .help = "Get the current size of free heap memory",
        .hint = NULL,
        .func = &free_mem,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&cmd) );
}

/* 'heap' command prints minumum heap size */
static int heap_size(int argc, char **argv)
{
    uint32_t heap_size = heap_caps_get_minimum_free_size(MALLOC_CAP_32BIT);
    ESP_LOGI(TAG, "min heap size: %u", heap_size);
    return 0;
}

static void register_heap()
{
    const esp_console_cmd_t heap_cmd = {
        .command = "heap",
        .help = "Get minimum size of free heap memory that was available during program execution",
        .hint = NULL,
        .func = &heap_size,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&heap_cmd) );

}

static int oled_img(int argc, char **argv)
{
    test_olcd_img();
    ESP_LOGI(TAG, "Draw test OLED LCD");
    return 0;
}

static void register_oled_img()
{
    const esp_console_cmd_t oled_img_cmd = {
        .command = "oled",
        .help = "Image OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_img,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_img_cmd) );
}

static int oled_flip(int argc, char **argv)
{
    test_olcd_flip();
    ESP_LOGI(TAG, "flipping OLED LCD");
    return 0;
}

static void register_oled_flip()
{
    const esp_console_cmd_t oled_flip_cmd = {
        .command = "flip",
        .help = "Flipping OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_flip,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_flip_cmd) );
}

static int oled_text(int argc, char **argv)
{
    test_olcd_text();
    ESP_LOGI(TAG, "Text test OLED LCD");
    return 0;
}

static void register_oled_text()
{
    const esp_console_cmd_t oled_text_cmd = {
        .command = "text",
        .help = "Text OLED LCD Drawing",
        .hint = NULL,
        .func = &oled_text,
    };
    ESP_ERROR_CHECK( esp_console_cmd_register(&oled_text_cmd) );
}
