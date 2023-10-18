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
  void init();
  void dashboard(LTMReader& TData);

  private:
  unsigned char stage=0;
};

#endif