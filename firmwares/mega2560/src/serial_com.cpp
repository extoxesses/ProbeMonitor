#include "../includes/serial_com.h"

void enableConnection(Stream& serial, String& ip) {
    String ssid = "";
    String password = "";
    getNetworkConfig(ssid, password);

    String cmd = ssid + "&" + password;
    sendCommand(serial, cmd, ip);
}

void manageCommand(Stream& serial, RtcDS1302<ThreeWire>& rtc, Probe* probes) {
    String cmd = serial.readStringUntil('\n');
    serialLog("manageCommand", INFO, cmd);

    if (MONITOR_CMD.equals(cmd)) {
        monitor(rtc, probes, false);
        String msg = "";
        monitorResponse(probes, msg);
        serial.print(msg);

    } else if (FILE_CMD.equals(cmd)) {
        sendFile(serial);

    } else {
        String errMsg = "Command '";
        errMsg.concat(cmd);
        errMsg.concat("' not found");
        serialLog("manageCommand", ERROR, errMsg);
    }
    serial.flush();
}

void monitorResponse(const Probe* probes, String& message) {
    for (short i = 0; i < IO_SENSORS; ++i) {
        String value;
        probeRespose(probes[i], value);

        message.concat(value);
        message.concat('&');
    }
    message = message.substring(0, message.length() - 1);
}

void probeRespose(const Probe& probe, String& msg) {
    msg = String(probe.id);
    msg.concat(";");
    msg.concat(String(probe.active));
    msg.concat(";");
    msg.concat(String(probe.value));
}

void sendCommand(Stream& serial, String& command, String& response) {
    serialLog("sendCommand", INFO, "Sending connection command...");
    response = "";
    if ((unsigned int) serial.availableForWrite() < command.length()) {
        serialLog("sendCommand", ERROR, "Unable to send message. No space left for command.");
        return;
    }

    serial.print(command);
    unsigned long timeout = millis() + SERIAL_TIMEOUT;
    while (!serial.available() && timeout > millis()) {
        // Wait for serial availability until TIMEOUT is reached
    }
    if (serial.available() && timeout > millis()) {
        response = serial.readStringUntil('\n');
        serialLog("sendCommand", INFO, "Done");
    } else {
        serialLog("sendCommand", ERROR, "Timeout expired.");
    }
}
