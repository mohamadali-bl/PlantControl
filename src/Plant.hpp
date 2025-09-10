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
const unsigned long PumpTime = 5 * 1e+3; //5s
const int Start_LightingTime = 7, End_LightingTime = 20;
const int Threshold = 900;

//Pins---------------------------------------------------------------------//
#define HUMIDITYSENSORPIN A3
#define LIGHTPIN 2
#define PUMPPIN 3

//Macros-------------------------------------------------------------------//
#define PumpingOFF(PUMPPIN) digitalWrite(PUMPPIN, LOW)
#define PumpingON(PUMPPIN)  digitalWrite(PUMPPIN, HIGH)
#define Lighting(LPIN, LIGHTSTATE) digitalWrite(LPIN, LIGHTSTATE) 

//-----------------------------------Class---------------------------------//
class PlantController {
  private:
    char daysOfWeek[7][5] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    uint8_t PumpPin, HumiditySensorPin, LightPin; //Pins
    int HumiditySensorValue = 0;
    unsigned long now, pumpStartTime = 0, lastLCDPrint = 0, lastSerialPrint = 0; //Time
    //Pump Functions
    void Pump(), StartPumping(), EndPumping();
    //Light Functions
    void Light();
    //Print Humidity
    void Humidity_LCD();
    //Set Objects
    void RTC_Set(), LCD_Set(); 
    //Helpful Functions
    void Space(){lcd.print(F("                "));} //16 space for print
    void Clear(uint8_t sa, uint8_t so) {lcd.setCursor(sa, so); Space();}
    //Object
    LiquidCrystal_I2C &lcd;
    RTC_DS1307 &rtc; DateTime Time;
  public:
    bool pumpOn, lightOn;
    PlantController(uint8_t Ppin, uint8_t Hpin, uint8_t Lpin, LiquidCrystal_I2C &lcd_ref, RTC_DS1307 &rtc_ref);
    void begin() {
      RTC_Set(); LCD_Set(); pinMode(PumpPin, OUTPUT); pinMode(LightPin, OUTPUT);
      PumpingOFF(PumpPin); Lighting(LightPin, LOW);
    } 
    void Main();
    void Seriall();
    void LCD();
    void Clock(), Calendar(), DayOfWeek();
};

#endif //PLANT_H
//*********************************************************//
