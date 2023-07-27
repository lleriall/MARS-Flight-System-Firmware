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

BroadcastedServer::BroadcastedServer() {}

void BroadcastedServer::begin() {
  // Set up ESP32 as an access point
  wifi_init_softap();

  // Start the server
  server = httpd_start(&config);

  // Serve the HTML webpage
  httpd_uri_t root_uri = {
      .uri       = "/",
      .method    = HTTP_GET,
      .handler   = sendWebpageHandler,
      .user_ctx  = this
  };
  httpd_register_uri_handler(server, &root_uri);

  // Handle /perform-task request
  httpd_uri_t task_uri = {
      .uri       = "/perform-task",
      .method    = HTTP_GET,
      .handler   = performTaskHandler,
      .user_ctx  = this
  };
  httpd_register_uri_handler(server, &task_uri);
}

void BroadcastedServer::handleClient() {
  httpd_poll_sessions(server);
}

esp_err_t BroadcastedServer::sendWebpageHandler(httpd_req_t *req) {
  BroadcastedServer *serverInstance = static_cast<BroadcastedServer*>(req->user_ctx);
  httpd_resp_send(req, responseXX, HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}

esp_err_t BroadcastedServer::performTaskHandler(httpd_req_t *req) {
  BroadcastedServer *serverInstance = static_cast<BroadcastedServer*>(req->user_ctx);
  // Perform the task
  // ...
  ESP_LOGI(TAG, "PRESSED");
  // Send a response back to the client
  httpd_resp_send(req, "Task completed", HTTPD_RESP_USE_STRLEN);
  return ESP_OK;
}

void BroadcastedServer::wifi_init_softap() {
  tcpip_adapter_init();
  wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
  ESP_ERROR_CHECK(esp_wifi_init(&cfg));

  wifi_config_t wifi_config = {};
  strcpy((char*)wifi_config.ap.ssid, "HIVE");
  strcpy((char*)wifi_config.ap.password, "password");
  wifi_config.ap.ssid_len = strlen("HIVE");
  wifi_config.ap.max_connection = 4;
  wifi_config.ap.authmode = WIFI_AUTH_WPA_WPA2_PSK;

  ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
  ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
  ESP_ERROR_CHECK(esp_wifi_start());
}

void BroadcastedServer::set_ALT_REGISTER() {
  // Not needed here
}

void BroadcastedServer::set_LAT_REGISTER() {
  // Not needed here
}

void BroadcastedServer::set_LNG_REGISTER() {
  // Not needed here
}