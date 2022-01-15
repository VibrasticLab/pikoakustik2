#include "my_includes.h"

#define EXAMPLE_ESP_WIFI_SSID   "elbiCare"
#define EXAMPLE_ESP_WIFI_PASS   "audiometri"
#define EXAMPLE_MAX_STA_CONN    2

bool wifi_ap = true;
tcpip_adapter_ip_info_t ipInfo;

static const char *TAG = "wifiAP";

static void wifiAP_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data){

    if(event_id==WIFI_EVENT_AP_STACONNECTED){
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" join, AID=%d", MAC2STR(event->mac), event->aid);
    }
    else if(event_id==WIFI_EVENT_AP_STADISCONNECTED){
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",MAC2STR(event->mac), event->aid);
    }
}

void start_wifiAP(void){
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifiAP_event_handler, NULL));

    wifi_config_t wifiap_cfg = {
        .ap = {
            .ssid = EXAMPLE_ESP_WIFI_SSID,
            .ssid_len = strlen(EXAMPLE_ESP_WIFI_SSID),
            .password = EXAMPLE_ESP_WIFI_PASS,
            .max_connection = EXAMPLE_MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        },
    };

    if(strlen(EXAMPLE_ESP_WIFI_PASS)==0){
        wifiap_cfg.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifiap_cfg));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "SoftAP OK. SSID:%s password:%s",EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);

    tcpip_adapter_get_ip_info(ESP_IF_WIFI_AP, &ipInfo);
    ESP_LOGI(TAG, "Dev IP: %s", ip4addr_ntoa(&ipInfo.ip));
}
