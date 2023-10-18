/* 
  Artificial Horizon for SSD1306 OLED with LTMReader Class
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "LTM2OLED.h"
#include "LTMReader.h"

LTM2OLED OLED;
LTMReader TData;
long nextdisplay=0;

void setup() 
{
  Serial.begin(9600);
  // Articicial Horizon 
  OLED.init(6,7);
  // Telemetry initialize
  TData.init();
  delay(500);
}

void loop() 
{
  TData.update();
  if (millis()>nextdisplay) 
  {
    OLED.dashboard(TData);  // Dashboard 
    nextdisplay=millis()+1000;
  };
  yield(); // let the ESP8266 do some unrelated things
}


