#ifndef XT_RADIATOR_MONITOR_UTILS_H
#define XT_RADIATOR_MONITOR_UTILS_H

// ThreeWire.h needs Arduino.h to properly work
// Do not change the includes order!
#include <Arduino.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include "constants.h"
#include "probe.h"

void initRTC(RtcDS1302<ThreeWire>& rtc);

void serialLog(const String& method, const String& type, const String& value);

void splitProperty(const String& property, String& key, String& value);

byte* stringToByte(const String& str);

#endif /*XT_RADIATOR_MONITOR_UTILS_H*/