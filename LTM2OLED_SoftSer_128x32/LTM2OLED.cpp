/* 
  Artificial Horizon and LTM dashboard for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "LTM2OLED.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "sinus_cosinus.cpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int cells = 0;

static const unsigned char PROGMEM plane_bmp[] =
{ 
  0b00000111, 0b11100000,
  0b00001000, 0b00010000,
  0b11111000, 0b00011111,
  0b00001000, 0b00010000,
  0b00000111, 0b11100000
};

void LTM2OLED::init(int pinSDA, int pinSCL) {
  Wire.begin(pinSDA, pinSCL);
  // Initialize OLED-display
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println("SSD1306 Init failed!");
    for(;;); // Don't proceed, loop forever
  }
  display.setTextColor(SSD1306_WHITE);
  display.display();
}

void LTM2OLED::dashboard(LTMReader& TData)
{
  short index;

  if (TData.armed) {stage=1;}
  if (cells==0) {cells=round(TData.voltage/3700);} // cells nur einmal festlegen!
  
  display.clearDisplay(); // Clear display buffer
  display.setCursor(0,0);
  if (stage==0) {
    display.setCursor(0,0);
    display.setTextSize(1);
    display.println("PRE");
    display.println("ARM");
    //GPS
    display.setTextSize(2);
    display.setCursor(25,0);
    display.print(fixTypes[TData.gpsFix]);
    display.print("-");
    display.print(TData.gpsSats);
    display.setTextSize(1);
    display.print("Sat");
    //Vbat
    display.setCursor(0,17);
    display.setTextSize(2);
    display.print(cells);
    display.print("S: ");
    display.print((double) TData.voltage/1000,2);
    display.print("V ");
  } else {
    drawHorizon(TData.roll, TData.pitch);
    display.setTextSize(2);
    display.setCursor(87,0);
    display.print((double) TData.altitude/100,0);
    display.setTextSize(1);
    display.setCursor(67,0);
    display.println("m");
    // Speed
    display.setTextSize(2);
    display.setCursor(87,17);   
    display.print(TData.groundSpeed);
    display.setTextSize(1);
    display.setCursor(67,17); 
    display.println("km");
    display.setCursor(67,24); 
    display.println("/h"); 
  };
  display.display(); // Update screen
}

void LTM2OLED::drawHorizon(short roll, short pitch)
{
  short x1, y1, x2, y2, hoehe, index, index_p;
  short links, rechts;
  links = 0; rechts = display.width()/2-1;
  display.drawLine(rechts, 0, rechts, display.height(), SSD1306_WHITE);
  display.drawLine(0, 0, 0, display.height(), SSD1306_WHITE);
  for(int i=1; i< display.height(); i+=10){
    display.drawLine(rechts-3, i, rechts, i, SSD1306_WHITE);
    display.drawLine(links+3, i, links, i, SSD1306_WHITE);
  };
  roll=-roll;
  if (roll<0) {index=360+roll;} else {index=roll;};
  if (pitch<0) {index_p=360+pitch;} else {index_p=pitch;};
  x1 = 32*cosinus[index]/1000+32;
  x2 = -32*cosinus[index]/1000+32;
  hoehe = -(display.height()/2)*sinus[index_p]/1000+(display.height()/2);
  y1 = (display.height()/2)*sinus[index]/1000+hoehe;
  y2 = -(display.height()/2)*sinus[index]/1000+hoehe;
  display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  display.drawBitmap(display.width()/4-7,display.height()/2-2,plane_bmp,16,5,SSD1306_WHITE);
}
