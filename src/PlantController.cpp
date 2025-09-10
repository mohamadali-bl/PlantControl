//*********************************************************//
#include "Plant.hpp"

/*
 * 
*/

//Object function----------------------------------------------------//
PlantController::PlantController(uint8_t Ppin, uint8_t Hpin, uint8_t Lpin, LiquidCrystal_I2C &lcd_ref, RTC_DS1307 &rtc_ref) :
  PumpPin(Ppin), HumiditySensorPin(Hpin), LightPin(Lpin), lcd(lcd_ref), rtc(rtc_ref), pumpOn(false), lightOn(false) {}

//MAIN---------------------------------------------------------------//
void PlantController::Main() {
  HumiditySensorValue = analogRead(HumiditySensorPin);
  Time = rtc.now(); now = millis(); //Value for Time
  Pump();  //Pump Control
  Light(); //Light Control
}

//PUMP---------------------------------------------------------------//
void PlantController::Pump() {
  if (HumiditySensorValue > Threshold && !pumpOn) {StartPumping();}  //Start Pumping
  if (pumpOn && ((now - pumpStartTime) >= PumpTime)) {EndPumping();} //Stop Pumping
}
//
void PlantController::StartPumping() {
  pumpStartTime = millis();
  pumpOn = true; PumpingON(PumpPin);
}
//
void PlantController::EndPumping() {
  pumpOn = false; PumpingOFF(PumpPin);
}

//LIGHT--------------------------------------------------------------------//
void PlantController::Light() {
  if ((Time.hour() >= Start_LightingTime)&&(Time.hour() <= End_LightingTime)) {if (!lightOn) {lightOn = true; Lighting(LightPin, LOW);}}
  else {lightOn = false; Lighting(LightPin, HIGH);}
}

//SET----------------------------------------------------------------------//
void PlantController::RTC_Set() {
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    Serial.flush();
    while(1) delay(20);
  }
  if (!rtc.isrunning()) {
    Serial.println(F("RTC is NOT running, let's set the time!"));
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2025, 9, 6, 21, 29, 20));
  }
}
//
void PlantController::LCD_Set() {
  lcd.init();      //Begin
  lcd.backlight(); //Backlight is ON
  lcd.setCursor(0, 0); lcd.print("LCD Set");
  delay(500);
}

//Humidity-----------------------------------------------------------------//
void PlantController::Humidity_LCD() {lcd.print(F("Humidity: ")); lcd.print(HumiditySensorValue);}

//CLOCK--------------------------------------------------------------------//
void PlantController::Clock() {
  lcd.print(Time.hour());
  lcd.print(F(":"));
  lcd.print(Time.minute());
  lcd.print(F(":"));
  lcd.print(Time.second());
}
//
void PlantController::Calendar() {
  lcd.print(Time.year());
  lcd.print(F("/"));
  lcd.print(Time.month());
  lcd.print(F("/"));
  lcd.print(Time.day());
}
//
void PlantController::DayOfWeek() {
  lcd.print(F("\""));
  lcd.print(daysOfWeek[Time.dayOfTheWeek()]);
  lcd.print(F("\""));
}
//PRINT--------------------------------------------------------------------//
void PlantController::Seriall() {
  now = millis();
  if (now - lastSerialPrint >= 1000) {
    lastSerialPrint = now;
    Serial.print(F("{\"PumpState\": "));
    Serial.print(pumpOn ? 1 : 0);
    Serial.print(F(", \"Humidity\": "));
    Serial.print(HumiditySensorValue);
    Serial.println(F("}"));
  }
}
//
void PlantController::LCD() {
  now = millis();
  if (now - lastLCDPrint >= 1000) {
    lastLCDPrint = now;
    if ((Time.second() >= 20 && Time.second() <= 25) || (Time.second() >= 40 && Time.second() <= 45)) {
      if (Time.second() == 20 || Time.second() == 40) {Clear(0, 1);}      //Clear Line 2
      lcd.setCursor(0, 0); Clock(); Space();                              //Print Clock
      lcd.setCursor(0, 1); Calendar(); lcd.setCursor(11, 1); DayOfWeek(); //Print Calender and Day
    }
    else {
      lcd.setCursor(0, 0); Clock(); Space();                              //Print Clock
      lcd.setCursor(0, 1); Humidity_LCD(); Space();                       //Print Humidity
    }
  }
}

//*********************************************************//
