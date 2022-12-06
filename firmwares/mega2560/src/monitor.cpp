#include "../includes/monitor.h"

void initProbes(Probe probes[]) {
    for(short i = 0; i < IO_SENSORS; ++i) {
        short cmd_pin = IO_0 + 2 * i;

        probes[i].id = i;
        probes[i].name = String(cmd_pin);

        // Enable probe communication
        probes[i].wire = new OneWire(cmd_pin);
        probes[i].channel = new DallasTemperature(probes[i].wire);
        probes[i].channel->begin();
    }
}

void monitor(RtcDS1302<ThreeWire>& rtc, Probe* probes, bool save) {
    serialLog("monitor", INFO, "Monitor...");

    for(short i = 0; i < IO_SENSORS; ++i) {
        float temp = readProbe(probes[i].channel);
        probes[i].value = temp;
        Serial.println(temp);
        if (temp > TEMP_THRESHOLD) {
            probes[i].active = true;
            if(save) {
                // saveReading(rtc, i, temp);
            }
        } else {
            probes[i].active = false;
        }
    }
}

float readProbe(DallasTemperature* channel) {
    channel->requestTemperatures();
    float temp = channel->getTempCByIndex(0);
    return temp;
}
