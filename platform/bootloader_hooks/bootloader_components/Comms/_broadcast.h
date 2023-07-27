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

#ifndef BROADCASTED_SERVER_H
#define BROADCASTED_SERVER_H

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_http_server.h"
//#include "page.h"

class BroadcastedServer {
public:
    BroadcastedServer();

    void begin();

    void handleClient();

    void performTask();

private:
    static esp_err_t sendWebpageHandler(httpd_req_t *req);
    static esp_err_t performTaskHandler(httpd_req_t *req);
    void wifi_init_softap();
    void set_ALT_REGISTER();
    void set_LAT_REGISTER();
    void set_LNG_REGISTER();

private:
    httpd_handle_t server;
    static const char *TAG;
};

#endif