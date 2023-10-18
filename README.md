# LTM2OLED
There are many ways to control your INAV flightcontroller with FPV or telemetry on your radio. But 
sometimes it would be nice to fly your model airplane within line of sight without FPV and with a 
small or older radio without all that telemetry. In this case a OLED display on your plane could be 
handy.

INAV has a native support for an OLED display, but updating this display in flight is not possible. 
The display uses to much CPU-time to be updated in  flight. You can only use it before arming. 

This project is a simple solution that will show a preflight display and live information after arming.

Therefor I connect a ESP8266 or ESP32 based development board to a free uart on the flight controller. 
INAV will transfer the information to the development board and this will feed a SSD1306 OLED display.

This projekt contains 4 sketches for different platforms:

Sketches for development boards that have to use Softwareserial (ESP8266, Atmega 328p, ...):
* LTM2OLED-SoftwareSerial
* LTM-Dump-SoftwareSerial

Sketches for development boards with free uart or hardware serial controller (ESP32C3, ESP32S3, ...):
* LTM2OLED-HardwareSerial
* LTM-Dump-HardwareSerial

LTM-Dump is used to Test the serial connection and sends the information to a connected serial monitor
within Arduino IDE. LTM2OLED only shows text information on the connected I2C SSD1306 OLED display.

You can find additional information in the documentation folder. 

This is a work in progress.