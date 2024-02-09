/* 
  Artificial Horizon for SSD1306 OLED with LTMReader Class
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "LTM2OLED.h"
//#define LTM_RXPIN 17  // default GPIO 14, uncomment and change only when needed
#include "LTMReader.h"

LTM2OLED OLED;
LTMReader TData;
long nextdisplay=0;

void setup() 
{
  // Articicial Horizon 
  OLED.init();
  // Telemetry initialize
  TData.init();
  delay(250);
}

void loop() 
{
  TData.update();
  if (millis()>nextdisplay) 
  {
    OLED.dashboard(TData);  // Dashboard with western artificial horizon
    nextdisplay=millis()+1000;
  };
  yield(); // let the ESP8266 do some unrelated things
}


