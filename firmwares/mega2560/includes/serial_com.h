#ifndef XT_RADIATOR_MONITOR_SERIAL_COMM_H
#define XT_RADIATOR_MONITOR_SERIAL_COMM_H

#include <Arduino.h>
#include "monitor.h"
#include "sd_manager.h"

void enableConnection(Stream& serial, String& response);

void manageCommand(Stream& serial, RtcDS1302<ThreeWire>& rtc, Probe* probes);

void monitorResponse(const Probe* probes, String& message);

void probeRespose(const Probe& probe, String& msg);

void sendCommand(Stream& serial, String& command, String& response);

#endif /*XT_RADIATOR_MONITOR_SERIAL_COMM_H*/