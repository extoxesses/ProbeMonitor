# Hardware properties and configurations

## Arduino swith configuration

Operation                                         |  1  |  2  |  3  |  4  |  5  |  6  |  7  |   8   |
------------------------------------------------- | --- | --- | --- | --- | --- | --- | --- | ----- |
CH340 connect to ESP8266 (upload sketch)          | OFF | OFF | OFF | OFF | ON  | ON  | ON  | NoUse | 
CH340 connect to ESP8266 (connect)                | OFF | OFF | OFF | OFF | ON  | ON  | OFF | NoUse |
CH340 connect to ATmega2560 (upload sketch)       | OFF | OFF | ON  | ON  | OFF | OFF | OFF | NoUse |
CH340 connect to Mega2560 COM3 connect to ESP8266 | ON  | ON  | ON  | ON  | OFF | OFF | OFF | NoUse |
Mega2560 + esp8266                                | ON  | ON  | OFF | OFF | OFF | OFF | OFF | NoUse |
All modules work independed                       | OFF | OFF | OFF | OFF | OFF | OFF | OFF | NoUse |

> **Note:** To enable the communication between the Mega2560 and the ESP8266, move the second switch in the `RXD3/TXD3` position.

## Serial communication
In this Arduino version, the Mega2560 and the ESP8266 are phisically connected each other. This allows a phisical communication between the two chips.
If you want to use serial communication (as I did in this project), you can use:
* `Serial` (port 0) on the ESP8266
* `Serial3` (port 3) on the Mega2560

## Micro SD card adatper connections
Plese, consider the [official Arduino's forum](https://forum.arduino.cc/t/sd-card-and-arduino-mega/55478/3).

PIN  |    Uno    | Mega2560 | 
---- | --------- | -------- |
Vcc  | 3.3/5 (V) | 3.3/5(V) |
SCK  |       13  |       52 |
MISO |       12  |       50 |
MOSI |       11  |       51 |
SS   |       10  |       53 |

## Temperature sensors
**DS18B20** - Vcc: 3.3V
> Pay attention on power: 5V are enough to destroy the source itself.
