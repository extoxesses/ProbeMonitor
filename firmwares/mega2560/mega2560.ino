#include "includes/serial_com.h"

ThreeWire rtcWire(RTC_DAT,RTC_CLK,RTC_RST);
RtcDS1302<ThreeWire> rtc(rtcWire);

String ip;
Probe probes[IO_SENSORS];

unsigned long duration = 500;
unsigned long lastRead = 0;

void setup() {
  Serial.begin(USB_BAUD);
  Serial3.begin(SERIAL3_BAUD);
  serialLog("setup", "INFO", "Start...");
  
  initRTC(rtc);
  initSD();
  enableConnection(Serial3, ip);
  serialLog("setup", "INFO", "ESP8266 IP: " + ip);

  initProbes(probes);
  delay(SYNC_DELAY);
  serialLog("setup", "INFO", "Mega2560 setup completed!");
}

void loop() {
  if (lastRead == 0 || lastRead + duration < millis()) {
    lastRead = millis();
    monitor(rtc, probes, true);
  }
  delay(2000);
}

void serialEvent3() {
  manageCommand(Serial3, rtc, probes);
}
