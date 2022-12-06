#include "../includes/utils.h"

void initRTC(RtcDS1302<ThreeWire>& rtc) {
    serialLog("initRTC", INFO, "Started RTC configurations...");
    rtc.Begin();
  
    if (!rtc.IsDateTimeValid()) {   
        RtcDateTime compiled(__DATE__, __TIME__);
        rtc.SetDateTime(compiled);
        String warn = "Invalid date-time. Use compile time: " + compiled;
        serialLog("initRTC", "WARN", warn);
    }
  
    rtc.SetIsWriteProtected(false);
    rtc.SetIsRunning(true);
  
    String msg = "RTC configured: ";
    msg.concat(ltoa(rtc.GetDateTime(), new char[9], 10));
    serialLog("initRTC", INFO, msg);
}

void serialLog(const String& method, const String& type, const String& value) {
    String msg = "[" + method + "]\t" + type + "\t" + value;
    Serial.println(msg);
}

void splitProperty(const String& property, String& key, String& value) {
    key = "";
    value = "";

    int idx = property.indexOf(':');
    key = property.substring(0, idx);

    // First character is the one after ':' connection
    value = property.substring(idx + 1, property.length());
    value.replace("\r","");
    value.replace("\n","");
}

byte* stringToByte(const String& str) {
    long size = str.length() + 1;
    byte buffer[size];
    str.getBytes(buffer, size);
    return buffer;
}
