#ifndef XT_RADIATOR_MONITOR_PROBE_MONITOR_H
#define XT_RADIATOR_MONITOR_PROBE_MONITOR_H

#include "constants.h"
#include "probe.h"
#include "sd_manager.h"
#include "utils.h"

void initProbes(Probe probes[]);

void monitor(RtcDS1302<ThreeWire>& rtc, Probe* probes, bool save);

float readProbe(DallasTemperature* channel);

#endif /*XT_RADIATOR_MONITOR_PROBE_MONITOR_H*/