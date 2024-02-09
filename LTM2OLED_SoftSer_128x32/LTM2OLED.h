/* 
  Artificial Horizon for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)
*/

#ifndef _LTM2OLED_
#define _LTM2OLED_
#include "LTMReader.h"

class LTM2OLED 
{
  public: 
  void init(int pinSDA = SDA, int pinSCL = SCL);
  void dashboard(LTMReader& TData);
  

  private:
  unsigned char stage=0;
  void drawHorizon(short roll, short pitch);
};

#endif