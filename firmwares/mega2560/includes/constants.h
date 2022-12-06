#ifndef XT_RADIATOR_MONITOR_CONST_H
#define XT_RADIATOR_MONITOR_CONST_H

#include <WString.h>

// Connector GPIO init pins
#define IO_0 30          // Sensor 0
#define IO_SENSORS 1     // Available sensors

const short RTC_CLK = 7; // RealTime Clock - Clock
const short RTC_DAT = 8; // RealTime Clock - Data
const short RTC_RST = 9; // RealTime Clock - Reset

// Serial properties
#define USB_BAUD 9600
#define SERIAL3_BAUD 115200

#define SERIAL_TIMEOUT 60000
#define SYNC_DELAY 500

const String MONITOR_CMD = "read";
const String FILE_CMD = "get-file";

// Network properties
#define NET_CONFIG_FILE "NETWORK.TXT"
const String CONFIG_SSID_KEY = "ssid";
const String CONFIG_PASSWORD_KEY = "password";

// Probles properties
#define TEMP_THRESHOLD -100.0
#define TEMP_FILE "monitor.csv"

// Logging properties
const String ERROR = "ERROR";
const String INFO = "INFO";

#endif /*XT_RADIATOR_MONITOR_CONST_H*/