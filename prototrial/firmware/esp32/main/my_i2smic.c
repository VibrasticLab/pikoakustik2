/**
 * example in use: https://github.com/pedrominatel/esp32-projects/blob/master/demo/sound_spectrum/main/i2s_spectrum_example_main.c
 */

#include "my_includes.h"

#define AUDIO_SAMPLE_RATE       (16000) // or 44100 if you like
#define I2S_CH                  I2S_NUM_0
#define SAMPLES_NUM             (1024)

int16_t y_cf[SAMPLES_NUM*2]; // For both Left-Right

static void micZero(void){
    for(int i=0 ; i< SAMPLES_NUM ; i++){
            y_cf[i*2 + 0] = 0;
            y_cf[i*2 + 1] = 0;
    }
}

static void micRaw(void){
    esp_err_t errMic;
    size_t bytesread;
    int16_t i2s_readraw_buff[SAMPLES_NUM];

    errMic= i2s_read(I2S_CH, (char *)i2s_readraw_buff, SAMPLES_NUM * 2, &bytesread, (100 / portTICK_RATE_MS));

    if(errMic != ESP_OK){
        printf("I2S read error\r\n");
    }
    else{
        for(int i=0 ; i< SAMPLES_NUM ; i++){
                y_cf[i*2 + 0] = i2s_readraw_buff[i];
                y_cf[i*2 + 1] = 0; // right channel fills with 0
        }
    }
}

static int micGet(int argc, char **argv){
    micZero();
    micRaw();

    for(int i=0 ; i< SAMPLES_NUM ; i++){
        printf("%i,",y_cf[i*2 + 0]);
        printf("%i,",y_cf[i*2 + 1]);
    }
    printf("0\r\n");

    return 0;
}

static void micRegister(void){
    const esp_console_cmd_t get = {
        .command = "get",
        .help = "Test data Mic (once)",
        .hint = NULL,
        .func = &micGet,
    };

    esp_console_cmd_register(&get);
}

void start_i2smic(void){
    
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
        .ws_io_num = 15,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = 23,
    };

    if(i2s_driver_install(I2S_CH, &micConf, 0, NULL) != ESP_OK){
        printf("I2S driver install error\r\n");
    }

    if(i2s_set_pin(I2S_CH, &micPin) != ESP_OK){
        printf("I2S pin set error\r\n");
    }

    if(i2s_set_clk(I2S_CH, AUDIO_SAMPLE_RATE, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO) != ESP_OK){
        printf("I2S clock set error\r\n");
    }

    micRegister();
}