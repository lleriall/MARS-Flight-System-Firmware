#ifndef BROADCASTED_SERVER_H
#define BROADCASTED_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include"page.h"

class BroadcastedServer {
    public:
        BroadcastedServer();

        void begin();

        void handleClient();

        void sendWebpage();

        void handleNotFound();

    private:
        WebServer server;
};

#endif