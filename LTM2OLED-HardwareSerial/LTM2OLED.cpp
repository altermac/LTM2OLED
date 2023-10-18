/* 
  Artificial Horizon for SSD1306 OLED
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "LTM2OLED.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int cells = 0;

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
    display.setTextSize(2);
    display.println("PRE-FLIGHT");
    display.setTextSize(1);
    //GPS
    display.setCursor(0,18);
    display.print("GPS: ");
    display.print(fixTypes[TData.gpsFix]);
    display.print("-fix ");
    display.print(TData.gpsSats);
    display.print(" Sats");
    display.setCursor(0,29);
    display.print((double) TData.latitude/10000000,5);
    display.print(" ");
    display.println((double) TData.longitude/10000000,5);
    //home
    display.setCursor(0,48);
    if (TData.homeFix) {
      display.print("Home set");
    } else {
      display.print("No Home");
    }
    //Vbat
    display.setCursor(0,57);
    display.print(cells);
    display.print("S ");
    display.print((double) TData.voltage/1000,2);
    display.println("V ");
    display.setCursor(64,50);
    display.setTextSize(2);
    if (cells>0) {display.print((double) TData.voltage/cells/1000,2);} else {display.print("0.00");}
    display.print("V");
  } else {
    if (TData.failsafe) {
      display.setCursor(0,0);
      display.setTextSize(2);
      display.print("FAILSAFE!");
      //GPS position
      display.setTextSize(1);
      display.setCursor(0,17);
      display.println("GPS position plane:");
      display.print((double) TData.latitude/10000000,5);
      display.print(" ");
      display.println((double) TData.longitude/10000000,5);
      //Homepoint
      display.println("GPS Home - Pilot:");
      display.print((double) TData.homeLatitude/10000000,5);
      display.print(" ");
      display.println((double) TData.homeLongitude/10000000,5);
      //Vbat
      display.setCursor(0,57);
      display.setTextSize(1);
      display.print(cells);
      display.print("S ");
      display.print((double) TData.voltage/1000,2);
      display.println("V ");
      display.setCursor(64,50);
      display.setTextSize(2);
      if (cells>0) {display.print((double) TData.voltage/cells/1000,2);} else {display.print("0.00");}
      display.print("V");
    } else {
      if (TData.armed){
        display.setCursor(0,0);
        display.setTextSize(2);
        display.print("armed ");
        display.println(flightModes[TData.flightmode]);
        //GPS
        display.setTextSize(1);
        display.setCursor(0,16);
        display.print("GPS: ");
        display.print(fixTypes[TData.gpsFix]);
        display.print("-fix ");
        display.print(TData.gpsSats);
        display.println(" Sats");
        display.print((double) TData.latitude/10000000,5);
        display.print(" ");
        display.println((double) TData.longitude/10000000,5);
        display.print("Alt: ");
        display.print((double) TData.altitude/100,2);
        display.println("m");
       // Speed
        display.setCursor(0,39);
        display.setTextSize(2);    
        display.print(TData.groundSpeed);
        display.setTextSize(1);
        display.println("km/h"); 
        //heading
        display.setCursor(64,39);
        display.print(TData.heading);
        index=round((TData.heading)/22.5);
        display.print((char)247);
        display.print("-");
        display.print(windrose[index]);
 
        // Vbat
        display.setCursor(0,57);
        display.print(cells);
        display.print("S ");
        display.print((double) TData.voltage/1000,2);
        display.println("V ");
        display.setCursor(64,50);
        display.setTextSize(2);
        if (cells>0) {display.print((double) TData.voltage/cells/1000,2);} else {display.print("0.00");}
        display.print("V");
      } else {
        display.setCursor(0,0);
        display.setTextSize(2);
        display.print(" disarmed");
         //GPS position
        display.setTextSize(1);
        display.setCursor(0,17);
        display.println("GPS position plane:");
        display.print((double) TData.latitude/10000000,5);
        display.print(" ");
        display.println((double) TData.longitude/10000000,5);
        //Homepoint
        display.println("GPS Home - Pilot:");
        display.print((double) TData.homeLatitude/10000000,5);
        display.print(" ");
        display.println((double) TData.homeLongitude/10000000,5);
        // Vbat
        display.setCursor(0,57);
        display.setTextSize(1);
        display.print(cells);
        display.print("S ");
        display.print((double) TData.voltage/1000,2);
        display.println("V ");
        display.setCursor(64,50);
        display.setTextSize(2);
        if (cells>0) {display.print((double) TData.voltage/cells/1000,2);} else {display.print("0.00");}
        display.print("V");
      }
    };
  };
  display.display(); // Update screen
}


