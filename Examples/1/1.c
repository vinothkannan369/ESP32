/* Simple HTTP Server Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
/*
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"
*/
#include <stdio.h>
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_http_client.h"
#include <esp_event.h>
#include <esp_system.h>
#include <esp_http_server.h>

/* A simple example that demonstrates how to create GET and POST
 * handlers for the web server.
 */
// WiFi
static void wifi_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    switch (event_id)
    {
    case WIFI_EVENT_STA_START:
        printf("WiFi connecting ... \n");
        break;
    case WIFI_EVENT_STA_CONNECTED:
        printf("WiFi connected ... \n");
        break;
    case WIFI_EVENT_STA_DISCONNECTED:
        printf("WiFi lost connection ... \n");
        break;
    case IP_EVENT_STA_GOT_IP:
        printf("WiFi got IP ... \n\n");
        break;
    default:
        break;
    }
}

// Client
esp_err_t client_event_handler(esp_http_client_event_handle_t evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        printf("Client HTTP_EVENT_ON_DATA: %.*s\n", evt->data_len, (char *)evt->data);
        break;

    default:
        break;
    }
    return ESP_OK;
}

void get_rest_function()
{
esp_http_client_config_t client_configuration = {
		.url = "http://worldclockapi.com/api/json/utc/now",
		.event_handler = client_event_handler};

esp_http_client_event_handle_t client = esp_http_client_init(&client_configuration);
esp_http_client_perform(client);
esp_http_client_cleanup(client);


}

void app_main(void)
{
nvs_flash_init();

esp_netif_init();
esp_event_loop_create_default();
esp_netif_create_default_wifi_sta();
wifi_init_config_t wifi_initiation = WIFI_INIT_CONFIG_DEFAULT();
 esp_wifi_init(&wifi_initiation);

 //2
 esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL);
   esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL);
   wifi_config_t wifi_configuration = {
       .sta = {
           .ssid = "Tree",
           .password = "aaaaaaaa"}};
   esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_configuration);
   // 3 - Wi-Fi Start Phase
   esp_wifi_start();
   // 4- Wi-Fi Connect Phase
   esp_wifi_connect();

   vTaskDelay(5000/portTICK_PERIOD_MS);
   get_rest_function();

}


