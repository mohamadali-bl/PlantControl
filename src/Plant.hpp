//*********************************************************//
#ifndef PLANT_H
#define PLANT_H
#include <Arduino.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

/*
 * 
*/

//Constants----------------------------------------------------------------//
extern RTC_DS1307 RTC;
extern LiquidCrystal_I2C LCD;

//Pins---------------------------------------------------------------------//
#define HUMIDITYSENSORPIN A3
#define LIGHTPIN 2
#define PUMPPIN 3

//Macros-------------------------------------------------------------------//
#define MyClass PlantController
inline void Pumping (uint8_t pin, bool state) {digitalWrite(pin, state);}
inline void Lighting(uint8_t pin, bool state) {digitalWrite(pin, state);}

//-----------------------------------Class---------------------------------//
class PlantController {
  private:
    char daysOfWeek[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    //Pins
    uint8_t PumpPin, DIYSensorPin, LightPin;
    //Values
    unsigned int DIYSensorValue = 0;
    unsigned long now, pumpStartTime = 0, lastLCDPrint = 0, lastSerialPrint = 0, lastLighting = 0;
    //Pump Functions
    void Pump();
    //Light Functions
    void Light();
    bool LightingTimeLine();
    //Set Objects
    void RTC_Set(), LCD_Set();
    //Object
    LiquidCrystal_I2C &lcd;
    RTC_DS1307 &rtc; DateTime Time;
  public:
    bool pumpFlag, lightFlag, rtcFlag;
    PlantController(uint8_t Ppin, uint8_t DIYpin, uint8_t Lpin, LiquidCrystal_I2C &lcd_ref, RTC_DS1307 &rtc_ref);
    void begin() {
      RTC_Set(); LCD_Set(); pinMode(PumpPin, OUTPUT); pinMode(LightPin, OUTPUT);
      Pumping(PumpPin, LOW); Lighting(LightPin, LOW);
    } 
    void Main();
    //Print Functions
    void Seriall();      //Serial Print (json)
    void Humidity_LCD(); //Humidity Sensor on LCD
    void LCD();          //Print LCD
    void Clock(), Calendar(), DayOfWeek(); //RTC Time
    bool LcdTimeLine();  //Change Print Shape
    void Space(){lcd.print(F("                "));}
    void Clear(uint8_t sa, uint8_t so) {lcd.setCursor(sa, so); Space();}
    
};

#endif //PLANT_H
//*********************************************************//
