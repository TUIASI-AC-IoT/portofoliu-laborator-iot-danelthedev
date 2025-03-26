/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/event_groups.h"
#include "esp_http_server.h"

#include "freertos/event_groups.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "lwip/sockets.h"
#include "lwip/netdb.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "soft-ap.h"
#include "http-server.h"

#include "../mdns/include/mdns.h"

#define CONFIG_LOCAL_PORT 80

#define WIFI_SCAN_TAG "WIFI_SCAN"

extern wifi_ap_record_t* ap_records;
extern uint16_t ap_count;

wifi_ap_record_t* wifi_scan_ssid(void)
{
    // Initialize Wi-Fi in STA mode
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    // Configure scan parameters
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true
    };

    // Start scanning
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));

    // Get the scan results
    ap_count = 0;
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ap_records = malloc(ap_count * sizeof(wifi_ap_record_t));
    if (ap_records == NULL) {
        ESP_LOGE(WIFI_SCAN_TAG, "Failed to allocate memory for AP records");
        return NULL;
    }
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_count, ap_records));

    // Log the scan results
    ESP_LOGI(WIFI_SCAN_TAG, "Found %d access points:", ap_count);
    for (int i = 0; i < ap_count; i++) {
        ESP_LOGI(WIFI_SCAN_TAG, "SSID: %s, RSSI: %d", ap_records[i].ssid, ap_records[i].rssi);
    }

    return ap_records; // Caller must free this memory
    ESP_ERROR_CHECK(esp_wifi_stop());

    // return a list of the SSIDs
    return ap_records;
}

void app_main(void)
{
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    uint16_t ap_count = 0; // Declare and initialize ap_count
    wifi_ap_record_t* ssids = wifi_scan_ssid();
    if (ssids == NULL) {
        ESP_LOGE(WIFI_SCAN_TAG, "Failed to scan Wi-Fi networks");
        return;
    }
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count)); // Get the number of APs
    for (int i = 0; i < ap_count; i++) {
        ESP_LOGI(WIFI_SCAN_TAG, "SSID: %s, RSSI: %d", ssids[i].ssid, ssids[i].rssi);
    }
    free(ssids); // Free the allocated memory

    // TODO: 1. Start the softAP mode
    wifi_init_softap();

     // TODO: 4. mDNS init (if there is time left)
    mdns_init();
    mdns_hostname_set("esp32-imbrea");
    mdns_instance_name_set("ESP32 Imbrea");

    // TODO: 2. Start the web server
    start_webserver();


}