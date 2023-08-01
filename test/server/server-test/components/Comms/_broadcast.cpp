/*MIT License

Copyright (c) 2023 limitless Aeronautics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "_broadcast.h"
#include <string>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include<stdio.h>
#include "lwip/err.h"
#include "lwip/sys.h"


/* The examples use WiFi configuration that you can set via project configuration menu.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define _ESP_WIFI_SSID      "HIVE2"
#define _ESP_WIFI_PASS      "HIVE_PASS"
#define _ESP_WIFI_CHANNEL   6
#define _MAX_STA_CONN       1

static const char *TAG = "wifi softAP";

void BroadcastedServer::wifi_event_handler(void* arg, esp_event_base_t event_base,
                                    int32_t event_id, void* event_data)
{
    if (event_id == WIFI_EVENT_AP_STACONNECTED) {
        wifi_event_ap_staconnected_t* event = (wifi_event_ap_staconnected_t*) event_data;
        //ESP_LOGI(TAG, "station "MACSTR" join, AID=%d",
                // MAC2STR(event->mac), event->aid);
    } else if (event_id == WIFI_EVENT_AP_STADISCONNECTED) {
        wifi_event_ap_stadisconnected_t* event = (wifi_event_ap_stadisconnected_t*) event_data;
        //ESP_LOGI(TAG, "station "MACSTR" leave, AID=%d",
                 //MAC2STR(event->mac), event->aid);
    }
}

void BroadcastedServer::wifi_init_softap(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &wifi_event_handler,
                                                        NULL,
                                                        NULL));

    wifi_config_t wifi_config = {
        .ap = {
        .ssid = _ESP_WIFI_SSID,
        .password = _ESP_WIFI_PASS,
        .channel = _ESP_WIFI_CHANNEL,
        .max_connection = _MAX_STA_CONN
        },
    };

    wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;
    

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_softap finished. SSID:%s password:%s channel:%d",
             _ESP_WIFI_SSID, _ESP_WIFI_PASS, _ESP_WIFI_CHANNEL);

    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.max_uri_handlers = 16;

    /* HTTP server configuration */

    httpd_uri_t root_uri = {
        .uri       = "/",
        .method    = HTTP_GET,
        .handler   = root_handler,
        .user_ctx  = NULL
    };

    httpd_uri_t LAT1_uri = {
        .uri       = "/GET_GPS",
        .method    = HTTP_POST,
        .handler   = handle_GPS_request,
        .user_ctx  = NULL
    };

    httpd_uri_t IMU1_uri = {
        .uri       = "/GET_IMU1",
        .method    = HTTP_POST,
        .handler   = handle_IMU1_request,
        .user_ctx  = NULL
    };

    httpd_uri_t W1_uri = {
        .uri       = "/GET_W1",
        .method    = HTTP_POST,
        .handler   = handle_W1_request,
        .user_ctx  = NULL
    };

    httpd_uri_t AMB1_uri = {
        .uri       = "/GET_AMB",
        .method    = HTTP_POST,
        .handler   = handle_AMB_request,
        .user_ctx  = NULL
    };


    // Start the HTTP server
    if (httpd_start(&server, &config) == ESP_OK) {
        //Register root
        httpd_register_uri_handler(server, &root_uri);
        httpd_register_uri_handler(server, &LAT1_uri);
        httpd_register_uri_handler(server, &IMU1_uri);
        httpd_register_uri_handler(server, &W1_uri);
        httpd_register_uri_handler(server, &AMB1_uri);
    }

}

std::string BroadcastedServer::packData(const std::string& id1, float value1,
                     const std::string& id2, float value2,
                     const std::string& id3, float value3,
                     const std::string& id4, float value4) {
    std::ostringstream packed;
    packed << id1 << value1 << "_" << id2 << value2 << "_" << id3 << value3 << "_" << id4 << value4;
    return packed.str();
}

/* Handler for the root ("/") endpoint */
esp_err_t BroadcastedServer::root_handler(httpd_req_t *req) {
    // Open the "index.html" file
    // Set the HTTP response content type as "text/html"
    httpd_resp_set_type(req, "text/html");

    // Send the "index.html" content as the HTTP response
    httpd_resp_send(req, responseXX, strlen(responseXX));

    return ESP_OK;
}

/* Handler for the "/GET_GPS" endpoint */
esp_err_t BroadcastedServer::handle_GPS_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

        std::string id1 = "LAT";
        double value1 = 56;
        std::string id2 = "LONG";
        double value2 = 78.50;
        std::string id3 = "SAT";
        double value3 = 72.34;
        std::string id4 = "ALT";
        double value4 = 40;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}


/* Handler for the "/IMU1" endpoint */
esp_err_t BroadcastedServer::handle_IMU1_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

        std::string id1 = "PITCH";
        double value1 = 98;
        std::string id2 = "ROLL";
        double value2 = 42;
        std::string id3 = "YAW";
        double value3 = 87;
        std::string id4 = "XXX";
        double value4 =22;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);
        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/W1" endpoint */
esp_err_t BroadcastedServer::handle_W1_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

       std::string id1 = "WFL";
        double value1 = 165;
        std::string id2 = "WFR";
        double value2 = 148;
        std::string id3 = "WRL";
        double value3 = 109;
        std::string id4 = "WRR";
        double value4 = 112;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}


esp_err_t BroadcastedServer::handle_AMB_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {

       std::string id1 = "OAT";
        double value1 = 165;
        std::string id2 = "PRESS";
        double value2 = 148;
        std::string id3 = "WX1";
        double value3 = 109;
        std::string id4 = "WX2";
        double value4 = 112;

        std::string packed_data = packData(id1, value1, id2, value2, id3, value3, id4, value4);

        // Send a response to the client
        httpd_resp_send(req, packed_data.c_str(), packed_data.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

