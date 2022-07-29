/**
 * @file my_adc.c
 * @brief ADC subsystem code
 *
 * @addtogroup Battery
 * @{
 */

#include "my_includes.h"

#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_6 // IO34
#define ADC_EXAMPLE_ATTEN           ADC_ATTEN_DB_11

extern int battPercent;

static const char *TAG_CH[1][10] = {{"ADC1_CH6"}};

static int adc_raw[1][10];
static const char *TAG = "ADC_BATT";

#if MY_ADC_VCAL
static esp_adc_cal_characteristics_t adc1_chars;
static uint32_t voltage = 0;
#endif

#if MY_ADC_VCAL
#define ADC_EXAMPLE_CALI_SCHEME     ESP_ADC_CAL_VAL_EFUSE_VREF

static bool vcal_enabled = FALSE;
static bool adc_calibration_init(void){
    esp_err_t ret;
    bool cali_enable = FALSE;

    ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);

    if (ret == ESP_ERR_NOT_SUPPORTED) {
        ESP_LOGW(TAG, "Calibration scheme not supported, skip software calibration");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        ESP_LOGW(TAG, "eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {
        cali_enable = TRUE;
        esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
    } else {
        ESP_LOGE(TAG, "Invalid arg");
    }

    return cali_enable;
}
#endif

void my_adcInit(void){
#if MY_ADC_VCAL
    vcal_enabled = adc_calibration_init();
#endif

    ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
    ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_EXAMPLE_CHAN0, ADC_EXAMPLE_ATTEN));

    ESP_LOGI(TAG, "ADC Initialization Complete");
}

void my_adcValue(void){
    adc_raw[0][0] = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
    ESP_LOGI(TAG_CH[0][0], "raw  data: %d", adc_raw[0][0]);
    printf("raw  data: %d\r\n", adc_raw[0][0]);
    printf("batt data: %d\r\n", adc_raw[0][0] * 100 / ADC_REFF_VAL);

#if MY_ADC_VCAL
    if (vcal_enabled) {
            voltage = esp_adc_cal_raw_to_voltage(adc_raw[0][0], &adc1_chars);
            ESP_LOGI(TAG_CH[0][0], "cali data: %d mV", voltage);
            printf("cali data: %d mV\r\n", voltage);
    }
#endif
}

void my_adcGetBatt(void){
    adc_raw[0][0] = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
    battPercent = adc_raw[0][0] * 100 / ADC_REFF_VAL;
}

 /** @} */
