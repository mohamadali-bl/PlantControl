//*************************************************************************//
#ifndef PLANTHEADER_H
#define PLANTHEADER_H
#include <Arduino.h>
#include <RTClib.h>            //RTC
#include <Wire.h>              //I2C
#include <LiquidCrystal_I2C.h> //LCD

 /******************************************************
 *  Project: Plant Monitoring System
 *  Author: Mohammad Ali Balvaieh
 *  Date: 2025-10
 *  Description: Arduino-based, soil moisture and time display system
 *  
 *  Copyright (c) 2025 Mohammad Ali
 *  All rights reserved.
 *  
 *  Permission is granted to use, copy, modify, and distribute
 *  this software for non-commercial purposes only, provided
 *  that this notice is included in all copies or substantial
 *  portions of the software.
 ******************************************************/

//Constants----------------------------------------------------------------//
extern RTC_DS1307 RTC;
extern LiquidCrystal_I2C LCD;
#define MC PlantClass //MyClass

//-----------------------------------Class---------------------------------//
class PlantClass {
  private:
    //Pins
    uint8_t PumpPin, DIYSensorPin, LightPin;
    //Values
    unsigned int DIYSensorValue = 0;
    unsigned long now, pumpStartTime = 0, lastLCDPrint = 0, lastLighting = 0, lastSerialPrint = 0;
    char daysOfWeek[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 
    //Set Objects
    void RTC_Set(), LCD_Set();
    //Objects
    LiquidCrystal_I2C &lcd;
    RTC_DS1307 &rtc; DateTime Time;
  public:
    //Flags
    bool pumpFlag, lightFlag, rtcFlag;
  //Controller Functions
    void Pump(); //Pump Controller
    void Light(), Lighting(bool); bool LightingTimeLine(); //Light Controller
  //Class Function
    PlantClass(uint8_t Ppin, uint8_t DIYpin, uint8_t Lpin, LiquidCrystal_I2C &lcd_ref, RTC_DS1307 &rtc_ref) :
    PumpPin(Ppin), DIYSensorPin(DIYpin), LightPin(Lpin), lcd(lcd_ref), rtc(rtc_ref) 
    {pumpFlag = false; lightFlag = false; rtcFlag = false;}
  //Main Function
    void Main();
  //Setup Functions
    void begin() { RTC_Set(); LCD_Set(); 
      pinMode(PumpPin, OUTPUT);   pinMode(LightPin, OUTPUT);
      digitalWrite(PumpPin, LOW); digitalWrite(LightPin, LOW);
    } 
  //Print Functions
    void Seriall();      //Serial Print (json)
    void Humidity_LCD(); //Humidity Sensor on LCD
    void LCD();          //Print LCD
    void Clock(), Calendar(), DayOfWeek(); //RTC Time
    bool LcdTimeLine();  //Change Print Shape
    void Space(){lcd.print(F("                        "));} //24 NULL space
    void Clear(uint8_t sa, uint8_t so) {lcd.setCursor(sa, so); Space();}
};

#endif //PLANTHEADER_H
//*************************************************************************//

