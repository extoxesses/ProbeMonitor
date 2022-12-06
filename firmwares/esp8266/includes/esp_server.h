#ifndef XT_RADIATOR_MONITOR_ESPSERVER_H
#define XT_RADIATOR_MONITOR_ESPSERVER_H

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#include "esp_constants.h"
#include "esp_serial_cmd.h"
#include "index.h"

extern ESP8266WebServer server;

void connect(const String& ssid, const String& password, IPAddress& ip);

void configureServer();

void rootHandler();

void downloadHandler();

void readHandler();

#endif /*XT_RADIATOR_MONITOR_ESPSERVER_H*/