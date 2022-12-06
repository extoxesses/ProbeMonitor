#ifndef XT_RADIATOR_MONITOR_ESP_SERIAL_CMD_H
#define XT_RADIATOR_MONITOR_ESP_SERIAL_CMD_H

#include <HardwareSerial.h>
#include <WString.h>
#include "esp_constants.h"

byte* buildErrorResponse(const String& command, const String& msg);

void getConnectionParams(const String& cmd, String& ssid, String& password);

void readAsync(String& response);

void sendCommand(const String& command, String& response);

unsigned long serialWait();

#endif /*XT_RADIATOR_MONITOR_ESP_SERIAL_CMD_H*/