#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "mqtt_client.h"

// ---------- Replace with your Wi-Fi ----------
#define WIFI_SSID      "YOUR_WIFI_NAME"
#define WIFI_PASS      "WIFI_PASS"

// ---------- MQTT Broker ----------
#define BROKER_URI     "MQTT_url"  // you can use public broker

static const char *TAG = "MQTT_EXAMPLE";

esp_mqtt_client_handle_t client;

// ---------- Wi-Fi Event Handler ----------
static void wifi_event_handler(void* arg, esp_event_base_t event_base,int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Connecting to Wi-Fi...");
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        ESP_LOGI(TAG, "Disconnected. Reconnecting...");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ESP_LOGI(TAG, "Got IP Address!");
    }
}

// ---------- MQTT Event Handler ----------
static void mqtt_event_handler(void *handler_args, esp_event_base_t base,int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT Connected!");
        while (1)
        
        {
            
            // Publish "hi" when connected
            esp_mqtt_client_publish(client, "esp32/test0", "Hello This is ESP32-c3", 0, 0, 0);
            ESP_LOGI(TAG, "Message 'Hello This is ESP32-c3' sent to topic esp32/test");
            vTaskDelay(5000);

        }
            break;

        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT Disconnected!");
            break;

        default:
            break;
    }
}

// ---------- Wi-Fi Init ----------
void wifi_init_sta(void)
{
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&cfg);

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID,&wifi_event_handler,NULL,&instance_any_id);
    esp_event_handler_instance_register(IP_EVENT,IP_EVENT_STA_GOT_IP,&wifi_event_handler,NULL,&instance_got_ip);

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };

    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();

    ESP_LOGI(TAG, "Wi-Fi initialization finished.");
}

// ---------- Main ----------
void app_main(void)
{
    nvs_flash_init();
    wifi_init_sta();

    // Configure MQTT
    esp_mqtt_client_config_t mqtt_cfg = {
    .broker.address.uri = BROKER_URI
};


    // Initialize and start client
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}
