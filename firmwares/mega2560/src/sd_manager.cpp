#include "../includes/sd_manager.h"

void initSD() {
    serialLog("initSD", INFO, "Init SD configuration...");
    if (SD.begin()) {
        serialLog("initSD", INFO, "SD initialization done!");
    } else {
        serialLog("initSD", ERROR, "SD initialization failed!");
    }
    delay(SYNC_DELAY);
}

void sendFile(Stream& serial) {
    File datalogger;
    openOrCreate(datalogger, FILE_READ);

    if (datalogger) {
        serialLog("sendFile", INFO, "Reading file");
        char value = 0x000;
        while(datalogger.available()) {
            if (serial.availableForWrite()) {
                value = datalogger.read();
                serial.write(value);
            }
            // delay(50);
        }
        serial.write(0x003);
        datalogger.close();
    } else {
        serialLog("sendFile", ERROR, "Unable to read datalogger file!");
    }
}

void getNetworkConfig(String& ssid, String& password) {
    File config = SD.open(NET_CONFIG_FILE);
    if (config) {
        while (config.available()) {
            String cmd = config.readStringUntil('\n');
            String key;
            String value;

            splitProperty(cmd, key, value);
            if (CONFIG_SSID_KEY.equals(key)) {
                ssid = value;
            } else if (CONFIG_PASSWORD_KEY.equals(key)) {
                password = value;
            }
        }
        config.close();
        
    } else {
        serialLog("getNetworkConfig",ERROR, "Unable to open file network configuration file");
    }
}

void openOrCreate(File& datalogger, uint8_t mode) {
    if (!SD.exists(TEMP_FILE)) {
        serialLog("openOrCreate", INFO, "File not exists. Create a new one!");
        datalogger = SD.open(TEMP_FILE, FILE_WRITE);
        datalogger.println("date;probe;temperature;");
        if (FILE_WRITE != mode) {
            datalogger.close();
            datalogger = SD.open(TEMP_FILE, mode);
        }
    } else {
        datalogger = SD.open(TEMP_FILE, mode);
    }
}

void saveReading(RtcDS1302<ThreeWire>& rtc, short idx, float temperature) {
    File datalogger;
    openOrCreate(datalogger, FILE_WRITE);

    // if the file opened okay, write on it
    if (datalogger) {
        serialLog("saveReading",INFO,"Add log to file");
        
        String log = String(rtc.GetDateTime());
        log.concat(";");
        log.concat(String(idx));
        log.concat(";");
        log.concat(String(temperature));
        log.concat(";");

        datalogger.println(log);
        datalogger.close();
    } else {
        serialLog("saveReading",ERROR,"Unable to read datalogger file!");
    }
}
