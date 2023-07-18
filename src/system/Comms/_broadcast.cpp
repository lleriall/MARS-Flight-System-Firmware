#include "_broadcast.h"

BroadcastedServer::BroadcastedServer() {}

void BroadcastedServer::begin() {
  // Set up ESP32 as an access point
  WiFi.softAP("HIVE", "password");

  IPAddress ipAddress(192, 168, 4, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(ipAddress, ipAddress, subnet);
  // Start the server
  server.begin();
}

void BroadcastedServer::handleClient() {
  server.handleClient();
}

void BroadcastedServer::sendWebpage() {
  // Serve the HTML webpage
  server.on("/", HTTP_GET, [this]() {
    server.send(200, "text/html", responseXX);
  });
}

void BroadcastedServer::handleNotFound() {
  // Handle page not found
  server.onNotFound([this]() {
    server.send(404, "text/plain", "Page not found");
  });
}