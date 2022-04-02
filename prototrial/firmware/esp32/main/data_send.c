/**
 * @file data_send.c
 * @brief Data Sending code
 *
 * @addtogroup IoT
 * @{
 */

 #include "my_includes.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_HOST    "27.112.78.108"
#define WEB_PATH    "/api/device/sendData/24"

#define MAX_HTTP_RECV_BUFFER 512
#define MAX_HTTP_OUTPUT_BUFFER 2048

static const char *TAG = "IoT";

static esp_err_t _http_event_hndl(esp_http_client_event_t *evt){
    static char *out_buffer;
    static int out_len;

    switch (evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;

        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;

        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;

        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;

        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);

            /*
             *  Check for chunked encoding is added as the URL for chunked encoding used in this example returns binary data.
             *  However, event handler can also be used in case chunked encoding is used.
             */

             if(!esp_http_client_is_chunked_response(evt->client)){
                 if(evt->user_data){
                     memcpy(evt->user_data + out_len, evt->data, evt->data_len);
                 }
                 else {
                     if(out_buffer==NULL){
                         out_buffer = (char*) malloc(esp_http_client_get_content_length(evt->client));
                         out_len = 0;

                         if (out_buffer==NULL) {
                            ESP_LOGE(TAG,"Failed to allocate memory for output buffer");
                            return ESP_FAIL;
                         }
                     }
                     memcpy(out_buffer + out_len, evt->data, evt->data_len);
                 }
                 out_len += evt->data_len;
             }

             break;

        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            if (out_buffer!=NULL) {
                // Response is accumulated in output_buffer. Uncomment the below line to print the accumulated response
                // ESP_LOG_BUFFER_HEX(TAG, output_buffer, output_len);
                free(out_buffer);
                out_buffer = NULL;
            }
            out_len = 0;
            break;

        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "HTTP_EVENT_DISCONNECTED");
            int mbedtls_err = 0;
            esp_err_t err = esp_tls_get_and_clear_last_error(evt->data, &mbedtls_err, NULL);

            if (err != 0) {
                if (out_buffer != NULL) {
                    free(out_buffer);
                    out_buffer = NULL;
                }
                out_len = 0;

                ESP_LOGI(TAG, "Last esp error code: 0x%x", err);
                ESP_LOGI(TAG, "Last mbedtls failure: 0x%x", mbedtls_err);
            }
            break;
    }

    return ESP_OK;
}

void send_DataGETDemo(void){

    esp_http_client_config_t config = {
        .host = WEB_HOST,
        .path = WEB_PATH,
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .event_handler = _http_event_hndl,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    page_sendDisplay(PAGE_SEND_TRY);
    esp_err_t err = esp_http_client_perform(client);

    page_sendDisplay(PAGE_SEND_WAIT);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP GET Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }

    page_sendDisplay(PAGE_SEND_OK);
    esp_http_client_cleanup(client);
}

void send_DataPOSTDemo(void){
    const char *json_data = "{\"tester\":\"VibrasticLab\", \
                              \"ch_0\":{\
                                  \"freq_0\":{\"freq\": 0.625,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_1\":{\"freq\": 1.250,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_2\":{\"freq\": 2.500,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_3\":{\"freq\": 5.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_4\":{\"freq\":10.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_5\":{\"freq\":20.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}\
                               },\
                               \"ch_1\":{\
                                  \"freq_0\":{\"freq\": 0.625,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_1\":{\"freq\": 1.250,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_2\":{\"freq\": 2.500,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_3\":{\"freq\": 5.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_4\":{\"freq\":10.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]},\
                                  \"freq_5\":{\"freq\":20.000,\"ampl\":1,\"record\":[6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1]}\
                                }\
                              }";

    char post_data[MAX_HTTP_OUTPUT_BUFFER];
    sprintf(post_data,"{\"audiogram\": %s}\n",json_data);

    esp_http_client_config_t config = {
        .host = WEB_HOST,
        .path = WEB_PATH,
        .transport_type = HTTP_TRANSPORT_OVER_TCP,
        .event_handler = _http_event_hndl,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);

    esp_http_client_set_method(client, HTTP_METHOD_POST);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

    page_sendDisplay(PAGE_SEND_TRY);
    esp_err_t err = esp_http_client_perform(client);

    page_sendDisplay(PAGE_SEND_WAIT);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                esp_http_client_get_status_code(client),
                esp_http_client_get_content_length(client));
    } else {
        ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    }

    page_sendDisplay(PAGE_SEND_OK);
    esp_http_client_cleanup(client);
}

/** @} */
