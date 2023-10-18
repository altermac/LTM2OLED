/* 
  Dump LTM to Serial Monitor for HardwareSerial
  This code is made for ESP32C3, ESP32S3 that can 
  use an internal Serialcontroller (UART).
  Copyright (c) 2023 altermac (MIT Licence)
*/
#include "LTMReader.h"

LTMReader TData;
long nextdisplay=0;

void setup() 
{
  Serial.begin(9600);
  TData.init(); //Set (RX,TX) for correct GPIO-pins, default (RX=10,TX=9)
}

void loop() 
{
  TData.update();
  if (millis()>nextdisplay) 
  {
    dump2Serial();
    nextdisplay=millis()+3000;
  };
  yield(); // let the ESP8266 do some unrelated things
}

void dump2Serial()
{
  Serial.print("*** ");
  if(TData.ltm_update) {Serial.print(" updated ");}
  Serial.println(" ***");
  Serial.print ("  Pitch: ");
  Serial.print (TData.pitch);
  Serial.print ("  Roll: ");
  Serial.print (TData.roll);
  Serial.print ("  Heading: ");
  Serial.print (TData.heading);

  Serial.print ("  VBat Voltage: ");
  Serial.print (TData.voltage);
  Serial.print ("  VBat Capacity used: ");
  Serial.println (TData.capacityUsed);
  Serial.print ("  RSSI: ");
  Serial.print (TData.rssi);
  Serial.print ("  airspeed (Pitot): ");
  Serial.print (TData.airspeed);
  Serial.println (" m/sec");

  if (TData.armed) { 
    Serial.print ("  armend ");
  } else {
    Serial.print ("  disarmend ");
  };
  if (TData.failsafe) {
    Serial.print ("  failsafe ");
  } else {
    Serial.print ("  no failsafe ");
  };
  Serial.print ("  Flightmode: ");
  Serial.print (TData.flightmode);
  Serial.print (" ");
  Serial.print (flightModes[TData.flightmode]);
  Serial.print ("  Sensor: ");
  Serial.println (TData.sensorStatus);
  
  Serial.print ("  altitude: ");
  Serial.print (TData.altitude);
  Serial.print ("  groundspeed: ");
  Serial.println (TData.groundSpeed); 
  

  Serial.print ("  GPS Fix: ");
  Serial.print (fixTypes[TData.gpsFix]);
  Serial.print ("  GPS Sats: ");
  Serial.print (TData.gpsSats);
  Serial.print ("  GPS hdop: ");
  Serial.println (TData.hdop);
  
  Serial.print ("  Position: Latitude: ");
  Serial.print ((double) TData.latitude/10000000,7);
  Serial.print ("  Longitude: ");
  Serial.println ((double) TData.longitude/10000000,7);
  
  if (TData.homeFix) { 
    Serial.print ("  Home position fixed");
  } else {
    Serial.print ("  No valid home position");
  };
  Serial.print ("  Home: Latitude: ");
  Serial.print ((double) TData.homeLatitude/10000000,7);
  Serial.print ("  Longitude: ");
  Serial.print ((double) TData.homeLongitude/10000000,7);;
  Serial.print ("  Altitude (cm): ");
  Serial.println (TData.homeAltitude);
}
