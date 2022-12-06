#ifndef XT_RADIATOR_MONITOR_SD_MANAGER_H
#define XT_RADIATOR_MONITOR_SD_MANAGER_H

#include <SPI.h>
#include <SD.h>
#include "utils.h"

void initSD();

void getNetworkConfig(String& ssid, String& password);

void openOrCreate(File& datalogger, uint8_t mode);

void saveReading(RtcDS1302<ThreeWire>& rtc, short idx, float temperature);

void sendFile(Stream& serial);

#endif /*XT_RADIATOR_MONITOR_SD_MANAGER_H*/