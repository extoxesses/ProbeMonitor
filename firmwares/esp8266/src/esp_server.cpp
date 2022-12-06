#include "../includes/esp_server.h"

void connect(const String& ssid, const String& password, IPAddress& ip) {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(SERVICE_WAIT);
  }
  ip = WiFi.localIP();
}

void configureServer() {
  server.on("/", rootHandler);
  server.on("/download", downloadHandler);
  server.on("/read", readHandler);
  server.begin();
}

void rootHandler() {
  server.send(200, "text/html", index_page);
}

void downloadHandler() {
  String file = "";
  sendCommand("get-file", file);
  server.send(200, "text/csv", file);
}

void readHandler() {
  String data = "";
  sendCommand("read", data);
  server.send(200, "text/plane", data);
}
