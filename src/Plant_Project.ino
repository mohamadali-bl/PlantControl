//*********************************************************//
#include "Plant.hpp"

/*
 * 
*/

RTC_DS1307 RTC; //Real Time Tiny I2C Clock
LiquidCrystal_I2C LCD(0x27, 16, 2); //LCD Character 16*2
//Pump, Humidity Level and Light Controller
PlantController Saye(PUMPPIN, HUMIDITYSENSORPIN, LIGHTPIN, LCD, RTC);

void setup() {
  delay(200);
  Serial.begin(9600); //Set Serial
  Saye.begin();       //Set Object
}
//
void loop() {
  Saye.Main(); Saye.LCD(); Saye.Seriall(); //Control a Plant 
}
//*********************************************************//
