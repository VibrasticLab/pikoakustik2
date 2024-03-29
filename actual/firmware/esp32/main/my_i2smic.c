/**
 * @file my_i2smic.c
 * @brief I2S Mic source
 *
 * @addtogroup I2S
 * @{
 */

/**
 * example in use: https://github.com/pedrominatel/esp32-projects/blob/master/demo/sound_spectrum/main/i2s_spectrum_example_main.c
 */

#include "my_includes.h"

extern uint16_t ambientDB;

/**
 * @brief Audio Sample Rate
 *
 */
#define AUDIO_SAMPLE_RATE       (44100)

/**
 * @brief I2S Port number
 *
 */
#define I2S_CH                  I2S_NUM_0

/**
 * @brief Sample Size
 *
 */
#define SAMPLES_NUM             (1024)

/**
 * @brief Tag for LCD command
 *
 */
static const char *TAG = "MIC";

/**
 * @brief Audio read buffer array
 *
 */
static int16_t i2s_readraw_buff[SAMPLES_NUM];

/**
 * @brief Zero-ing buffer array
 *
 */
static void micZero(void){
    for(int i=0 ; i< SAMPLES_NUM ; i++){
            i2s_readraw_buff[i] = 0;
    }
}

/**
 * @brief Get Raw value into buffer array
 *
 */
static void micRaw(void){
    esp_err_t errMic;
    size_t bytesread;

    errMic= i2s_read(I2S_CH, (char *)i2s_readraw_buff, sizeof(i2s_readraw_buff), &bytesread, (100 / portTICK_RATE_MS));

    if(errMic != ESP_OK) printf("I2S read error\r\n");
}

/**
 * @brief Get maximum value as dB
 *
 * @return uint16_t Max value (dB)
 */
static uint16_t micMax(void){
    uint16_t valMax = 0;
    uint16_t valAbs = 0;

    micZero();
    micRaw();

    for(int i=0 ; i< SAMPLES_NUM ; i++){
            valAbs = abs(i2s_readraw_buff[i]);
            if(valAbs >= valMax) valMax = valAbs;
    }

    return valMax;
}

#if MY_MIC_CMD
/**
 * @brief Print buffer array
 *
 */
static void micGet(void){
    micZero();
    micRaw();

    for(int i=0 ; i< SAMPLES_NUM ; i++){
        printf("%i,",i2s_readraw_buff[i]);
    }
}

/**
 * @brief Print raw read buffer command
 *
 * @param argc argument counter
 * @param argv argument values
 * @return int return status
 */
static int micGetFunc(int argc, char **argv){
    micGet();
    printf("0\r\n");

    return 0;
}

/**
 * @brief Get Max value command
 *
 * @param argc argument counter
 * @param argv argument values
 * @return int return status
 */
static int micMaxFunc(int argc, char **argv){
    uint16_t maxVal = 0;

    maxVal = micMax();
    printf("micMax =  %i\r\n", maxVal);

    return 0;
}

/**
 * @brief Register Mic Commands
 *
 */
static void micRegister(void){
    const esp_console_cmd_t get = {
        .command = "mic-get",
        .help = "Test data Mic (once)",
        .hint = NULL,
        .func = &micGetFunc,
    };

    const esp_console_cmd_t max = {
        .command = "mic-max",
        .help = "Test Max Mic (once)",
        .hint = NULL,
        .func = &micMaxFunc,
    };

    esp_console_cmd_register(&get);
    esp_console_cmd_register(&max);
}
#endif

#if MY_MIC_TASK
/**
 * @brief Get Max value dB routine
 *
 * @param pvParameter Task paramaters
 */
static void micMaxTask(void *pvParameter){
    while(1){
        ambientDB = micMax();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
#endif

/**
 * @brief I2S Mic Initialization
 *
 */
void my_i2smicInit(void){

    i2s_config_t micConf = {
        .mode = I2S_MODE_MASTER | I2S_MODE_RX,
        .sample_rate = AUDIO_SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, //LRC pin must to GND
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 8,
        .dma_buf_len = 256,
    };

    i2s_pin_config_t micPin = {
        .bck_io_num = 14,
        .ws_io_num = 13,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 23,
    };

    if(i2s_driver_install(I2S_CH, &micConf, 0, NULL) != ESP_OK){
        ESP_LOGE(TAG, "I2S driver install error\r\n");
    }

    if(i2s_set_pin(I2S_CH, &micPin) != ESP_OK){
        ESP_LOGE(TAG, "I2S pin set error\r\n");
    }

    if(i2s_set_clk(I2S_CH, AUDIO_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO) != ESP_OK){
        ESP_LOGE(TAG, "I2S clock set error\r\n");
    }

    ambientDB = micMax();

#if MY_MIC_TASK
    xTaskCreate(&micMaxTask, "mic_task", 4096, NULL, tskIDLE_PRIORITY, NULL);
#endif

#if MY_MIC_CMD
    micRegister();
#endif
}

/** @} */
