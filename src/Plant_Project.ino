//*********************************************************//
#include "PlantHeader.hpp"

/*
 * 
*/

//Set Pins
#define HUMIDITYSENSORPIN A3
#define LIGHTPIN 2
#define PUMPPIN 3

RTC_DS1307 RTC;                     //Real Time Tiny I2C Clock
LiquidCrystal_I2C LCD(0x27, 16, 2); //LCD Character 16*2
//PlantClass NameOFPlant(Pump, SENSOR, LIGHT, LCD, RTC)
PlantClass Saye(PUMPPIN, HUMIDITYSENSORPIN, LIGHTPIN, LCD, RTC);

void setup() {
  delay(200);
  Serial.begin(9600); //Set Serial
  Saye.begin();       //Set Object
}
//
void loop() {
  Saye.Main(); Saye.LCD(); Saye.Seriall();
}
//*********************************************************//
