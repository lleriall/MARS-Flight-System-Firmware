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

    httpd_uri_t button_uri = {
        .uri       = "/button",
        .method    = HTTP_POST,
        .handler   = handle_button_request,
        .user_ctx  = NULL
    };

    httpd_uri_t LAT1_uri = {
        .uri       = "/GET_LAT",
        .method    = HTTP_POST,
        .handler   = handle_LAT_request,
        .user_ctx  = NULL
    };

    httpd_uri_t LONG1_uri = {
        .uri       = "/GET_LONG",
        .method    = HTTP_POST,
        .handler   = handle_LONG_request,
        .user_ctx  = NULL
    };

    httpd_uri_t SAT1_uri = {
        .uri       = "/GET_SAT",
        .method    = HTTP_POST,
        .handler   = handle_SAT_request,
        .user_ctx  = NULL
    };

    httpd_uri_t PTCH1_uri = {
        .uri       = "/GET_PTCH",
        .method    = HTTP_POST,
        .handler   = handle_PTCH_request,
        .user_ctx  = NULL
    };

    httpd_uri_t RLL1_uri = {
        .uri       = "/GET_RLL",
        .method    = HTTP_POST,
        .handler   = handle_RLL_request,
        .user_ctx  = NULL
    };

    httpd_uri_t YAW1_uri = {
        .uri       = "/GET_YAW",
        .method    = HTTP_POST,
        .handler   = handle_YAW_request,
        .user_ctx  = NULL
    };

    httpd_uri_t WFL1_uri = {
        .uri       = "/GET_WFL",
        .method    = HTTP_POST,
        .handler   = handle_WFL_request,
        .user_ctx  = NULL
    };

    httpd_uri_t WFR1_uri = {
        .uri       = "/GET_WFR",
        .method    = HTTP_POST,
        .handler   = handle_WFR_request,
        .user_ctx  = NULL
    };

    httpd_uri_t WRL1_uri = {
        .uri       = "/GET_WRL",
        .method    = HTTP_POST,
        .handler   = handle_WRL_request,
        .user_ctx  = NULL
    };

    httpd_uri_t WRR1_uri = {
        .uri       = "/GET_WRR",
        .method    = HTTP_POST,
        .handler   = handle_WRR_request,
        .user_ctx  = NULL
    };

    httpd_uri_t OAT1_uri = {
        .uri       = "/GET_OAT",
        .method    = HTTP_POST,
        .handler   = handle_OAT_request,
        .user_ctx  = NULL
    };

    httpd_uri_t PRESS1_uri = {
        .uri       = "/GET_PRESS",
        .method    = HTTP_POST,
        .handler   = handle_PRESS_request,
        .user_ctx  = NULL
    };


    // Start the HTTP server
    if (httpd_start(&server, &config) == ESP_OK) {
        //Register root
        httpd_register_uri_handler(server, &root_uri);
        // Register the "/button" URI handler
        //httpd_register_uri_handler(server, &button_uri);
        httpd_register_uri_handler(server, &LAT1_uri);
        httpd_register_uri_handler(server, &LONG1_uri);
        httpd_register_uri_handler(server, &SAT1_uri);
        httpd_register_uri_handler(server, &PTCH1_uri);
        httpd_register_uri_handler(server, &RLL1_uri);
        httpd_register_uri_handler(server, &YAW1_uri);
        httpd_register_uri_handler(server, &WFL1_uri);
        httpd_register_uri_handler(server, &WFR1_uri);
        httpd_register_uri_handler(server, &WRL1_uri);
        httpd_register_uri_handler(server, &WRR1_uri);
        httpd_register_uri_handler(server, &OAT1_uri);
        httpd_register_uri_handler(server, &PRESS1_uri);
    }

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

/* Handler for the "/button" endpoint */
esp_err_t BroadcastedServer::handle_button_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the button is pressed
        // For example, toggle an LED, control a motor, etc.
        // Implement your action here...

        // Send a response to the client
        const char *response = "Button Pressed";
        httpd_resp_send(req, response, strlen(response));
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_LAT" endpoint */
esp_err_t BroadcastedServer::handle_LAT_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_LONG" endpoint */
esp_err_t BroadcastedServer::handle_LONG_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_SAT_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_PTCH_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_RLL_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_YAW_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_WFL_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_WFR_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_WRL_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

/* Handler for the "/GET_SAT" endpoint */
esp_err_t BroadcastedServer::handle_WRR_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_OAT_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}

esp_err_t BroadcastedServer::handle_PRESS_request(httpd_req_t *req) {
    // Check if the request is a POST request
    if (req->method == HTTP_POST) {
        // Perform the action you want to execute when the endpoint is requested
        // Providing a seed value for randomness
        srand((unsigned) time(NULL));

        // Get a random number
        int random = rand();
        std::string str = std::to_string(random);

        // Send a response to the client
        httpd_resp_send(req, str.c_str(), str.length());
        return ESP_OK;
    }

    // If the request is not a POST request, return 404 Not Found
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Not Found");
    return ESP_OK;
}