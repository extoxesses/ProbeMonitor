#ifndef XT_RADIATOR_MONITOR_PROBE_H
#define XT_RADIATOR_MONITOR_PROBE_H

#include <DallasTemperature.h>
#include <OneWire.h>

struct Probe {
  int id;
  String name = "";
  OneWire* wire;
  DallasTemperature* channel;
  bool active;
  float value;
};

#endif /*XT_RADIATOR_MONITOR_PROBE_H*/