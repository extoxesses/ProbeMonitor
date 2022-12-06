#include "../includes/esp_serial_cmd.h"

byte* buildErrorResponse(const String& command, const String& msg) {
    String log = "[";
    log.concat(command);
    log.concat("] ERROR - ");
    log.concat(msg);

    byte* response = (byte*) malloc(log.length());
    // memcpy(response, log.data(), log.length());
    log.getBytes(response, log.length(), 0);
    return response;
}

void getConnectionParams(const String& cmd, String& ssid, String& password) {
    int idx = cmd.indexOf('&');
    ssid = cmd.substring(0, idx);

    // First character is the one after '&' connection
    password = cmd.substring(idx + 1, cmd.length());
}

void readAsync(String& response) {
    response = "";
    char lastChar = NULL_CHAR;

    do {
        if (Serial.available()) {
            lastChar = Serial.read();
            response += lastChar;
        }
    } while (EOF_CHAR != lastChar);
}

void sendCommand(const String& command, String& response) {
    if ((unsigned int) Serial.availableForWrite() < command.length()) {
        buildErrorResponse(command, "Unable to send command. No space left for command.");
    }

    Serial.print(command);
    unsigned long timeout = serialWait();

    if (Serial.available() && timeout > millis()) {
        readAsync(response);
    } else {
        buildErrorResponse(command, "Timeout expired.");
    }
}

unsigned long serialWait() {
    unsigned long timeout = millis() + SERIAL_TIMEOUT;
    while (!Serial.available() && timeout > millis()) {
        // Wait for serial availability until TIMEOUT is reached
    }
    return timeout;
}

