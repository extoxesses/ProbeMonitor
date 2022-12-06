#include "includes/esp_serial_cmd.h"
#include "includes/esp_server.h"

ESP8266WebServer server(SERVER_PORT);

void setup() {
  // Enable hardware serial channel
  Serial.begin(COMM_BAUD);
  while (!Serial.available()) {
    // Wait for Mega2560 init command
    delay(SERVICE_WAIT);
  }
  
  // Get connection params
  String cmd = Serial.readStringUntil('\n');
  String ssid = "";
  String password = "";
  getConnectionParams(cmd, ssid, password);

  // Connect to local WiFi and enable server
  IPAddress address;
  connect(ssid, password, address);
  configureServer();
  
  // Eventually, returns the local IP to the Mega2560
  Serial.println(address);
}

void loop() {
  server.handleClient();
}
