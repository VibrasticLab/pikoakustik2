/**
 * @file my_shell.c
 * @brief UART Shell source
 *
 * @addtogroup Console
 * @{
 */

#include "my_includes.h"

#if MY_UART_BAUDCUSTOM
#define MY_UART_BAUDRATE   38400
#else
#define MY_UART_BAUDRATE   115200
#endif

#if MY_UART_NOPROMPT
const char* prompt = "";
#else
const char* prompt = "esp32> ";
#endif

/**
 * @brief UART0 Console Start
 *
 */
static void console_Init(void){
    const uart_config_t uartConf = {
        .baud_rate = MY_UART_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .source_clk = UART_SCLK_REF_TICK,
    };

    const esp_console_config_t consoleConf = {
        .max_cmdline_args = 8,
        .max_cmdline_length = 256,
    };

    fflush(stdout);
    fsync(fileno(stdout));
    setvbuf(stdin, NULL,_IONBF, 0);

#if MY_UART_NUM1
    esp_vfs_dev_uart_port_set_rx_line_endings(UART_NUM_1, ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_port_set_tx_line_endings(UART_NUM_1, ESP_LINE_ENDINGS_CRLF);

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_1, MY_UART_BUFF_SIZE, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_1, &uartConf));
    esp_vfs_dev_uart_use_driver(UART_NUM_1);
#else
    esp_vfs_dev_uart_port_set_rx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CR);
    esp_vfs_dev_uart_port_set_tx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CRLF);

    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, MY_UART_BUFF_SIZE, 0, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uartConf));
    esp_vfs_dev_uart_use_driver(UART_NUM_0);
#endif

    esp_console_init(&consoleConf);

    linenoiseAllowEmpty(true);
    linenoiseHistorySetMaxLen(100);
}

void my_shellInit(void){
  console_Init();
  esp_console_register_help_command();

  my_registerCommands();

#if MY_USE_OLCD
  my_register_oled();
#endif

#if MY_UART_SILENT
#else
  printf("System Configured\n");
#endif

#if MY_UART_DUMB
  linenoiseSetDumbMode(1);
#endif
}

int my_shellLoop(void){
  char* line = linenoise(prompt);
  if(line==NULL){
      return 1;
  }

  if(strlen(line)>0){
      linenoiseHistoryAdd(line);
  }

  int ret;
#if MY_UART_SILENT
  esp_console_run(line, &ret);
#else
  esp_err_t err = esp_console_run(line, &ret);
  printf("Command: %s\n",line);

  if (err == ESP_ERR_NOT_FOUND) {
      printf("Unrecognized command\n");
  } else if (err == ESP_ERR_INVALID_ARG) {
      printf("Invalid command arguments\n");
  } else if (err == ESP_OK && ret != ESP_OK) {
      printf("Command returned non-zero error code: 0x%x (%s)\n", ret, esp_err_to_name(ret));
  } else if (err != ESP_OK) {
      printf("Internal error: %s\n", esp_err_to_name(err));
  }
#endif

  linenoiseFree(line);
  return 0;
}

/** @} */
