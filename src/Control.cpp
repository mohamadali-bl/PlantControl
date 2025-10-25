//*********************************************************//
#include "PlantHeader.hpp"

/*
 * 
*/

//Constants----------------------------------------------------------------//
const unsigned int PumpingTimeLine = 2 * 1e+3; //2s
const unsigned int Threshold = 800;
const unsigned int Start_Lighting = 7, End_Lighting = 20;
const unsigned long LightingTime = 5UL * 60UL * 60UL * 1000UL; //5h

//MAIN---------------------------------------------------------------//
void MC::Main() {
  Time = rtc.now(); now = millis(); //Update Time
  DIYSensorValue = analogRead(DIYSensorPin);
  if ((DIYSensorValue <= 1030) && (DIYSensorValue > 1)) {
    Pump();  //Pump Control
    Light(); //Light Control
  }
}
//PUMP---------------------------------------------------------------//
void MC::Pump() {
  if (!pumpFlag && (DIYSensorValue > Threshold)) {               //Start Pumping
    pumpStartTime = millis();
    pumpFlag = true; digitalWrite(PumpPin, HIGH);
  }  
  if (pumpFlag  && ((now - pumpStartTime) >= PumpingTimeLine)) { //Stop Pumping
    pumpFlag = false; digitalWrite(PumpPin, LOW);}   
}
//LIGHT--------------------------------------------------------------------//
void MC::Light() {
  if (rtcFlag == true) {
    if (LightingTimeLine()) if (!lightFlag) {Lighting(true);} //Lighting ON
    else {Lighting(false);}                                   //Lighting OFF
  }
  else {
    now = millis();
    if ((now - lastLighting) >= LightingTime) {
      lastLighting = now;
      lightFlag = !lightFlag;
      digitalWrite(LightPin, lightFlag ? LOW : HIGH);
    }
  }
}
//
bool MC::LightingTimeLine() {
  if ((Time.hour() >= Start_Lighting)&&(Time.hour() <= End_Lighting)) {return true;}
  else {return false;}
}
//
void MC::Lighting(bool Flag){
  if (Flag){lightFlag = true; digitalWrite(LightPin, LOW);}
  else {lightFlag = false; digitalWrite(LightPin, HIGH);}
}
//SET----------------------------------------------------------------------//
void MC::RTC_Set() {
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    Serial.flush(); rtcFlag = false;
  }
  else {rtcFlag = true;}
  if (!rtc.isrunning()) {
    Serial.println(F("RTC Error..."));
    Serial.print(F("RTC is NOT running, let's set the time!"));
    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    //rtc.adjust(DateTime(2025, 9, 6, 21, 29, 20));
  }
}
//
void MC::LCD_Set() {
  lcd.init();             //Begin
  lcd.backlight();        //Backlight is ON
  //RTC Validation
  if (!rtcFlag) {
    Clear(0, 0); Clear(0, 1);
    lcd.setCursor(0, 0); lcd.print(F("Couldn't find RTC"));
    lcd.setCursor(0, 1); lcd.print(F("Time Not Real"));
    delay(5000); return;
  }
  if (!rtc.isrunning()) { //RTC Error
    Clear(0, 0); Clear(0, 1);
    lcd.setCursor(0, 0); lcd.print(F("RTC Error..."));
    lcd.setCursor(0, 1); lcd.print(F("let's set time"));
    delay(5000);
  }
  else {lcd.setCursor(0, 0); lcd.print("LCD Set"); delay(500);} //Valid
}
//REAL-TIME----------------------------------------------------------------//
void MC::Clock() {
  lcd.print(Time.hour());
  lcd.print(F(":"));
  lcd.print(Time.minute());
  lcd.print(F(":"));
  lcd.print(Time.second());
}
//
void MC::Calendar() {
  lcd.print(Time.year());
  lcd.print(F("/"));
  lcd.print(Time.month());
  lcd.print(F("/"));
  lcd.print(Time.day());
}
//
void MC::DayOfWeek() {
  lcd.print(F("\""));
  lcd.print(daysOfWeek[Time.dayOfTheWeek()]);
  lcd.print(F("\""));
}
//PRINT--------------------------------------------------------------------//
void MC::Seriall() {

/* 
 * Print Pump and Light State and
 * Sensor Value On Serial With Json Type
*/
  now = millis();
  if (now - lastSerialPrint >= 1000) {
    lastSerialPrint = now;
    Serial.print(F("{\"PumpState\": "));Serial.print(pumpFlag ? 1 : 0);
    Serial.print(F(", \"Humidity\": "));Serial.print(DIYSensorValue);
    Serial.print(F(", \"LightState\": "));Serial.print(lightFlag ? 1 : 0);
    Serial.println(F("}"));
  }
}
//
void MC::LCD() {
  now = millis();
  if (now - lastLCDPrint >= 1000) {                  //Print One sedonds
    lastLCDPrint = now;
    if (rtcFlag) { //With RTC Module
      if (LcdTimeLine()) {                             //Change Shape Of Print
        if (Time.second() == 20 || Time.second() == 40) {Clear(0, 0); Clear(0, 1);} //Clear Lines
        lcd.setCursor(0, 0);  Clock(); Space();        //Print Clock
        lcd.setCursor(0, 1);  Calendar();              //Print Calender
        lcd.setCursor(11, 1); DayOfWeek();             //Print Days
      }
      else {
        lcd.setCursor(0, 0); Clock();        Space();  //Print Clock
        lcd.setCursor(0, 1); Humidity_LCD(); Space();  //Print Humidity
      }
    }
    else { //Without RTC Module
      Clear(0, 0); Clear(0, 1);
      lcd.setCursor(0, 1); Humidity_LCD(); Space();    //Print Humidity
    }
  }
}
//
bool MC::LcdTimeLine() {
  if (((Time.second() >= 20)&&(Time.second() <= 25))||((Time.second() >= 40)&&(Time.second() <= 45))) {return true;}
  else {return false;}
}
//
void MC::Humidity_LCD() {lcd.print(F("Humidity: ")); lcd.print(DIYSensorValue);}

//*********************************************************//
