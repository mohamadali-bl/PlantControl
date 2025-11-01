========================================================================================================
# 🌱 Plant Monitoring System
**Arduino-Based Soil Moisture & Time Display**

---

## Overview
The **Plant Monitoring System** simplifies indoor plant maintenance 
by providing real-time soil moisture measurements alongside the current time.  
It uses an analog soil moisture sensor and a 16x2 LCD to give users a clear view of their plant’s needs
minimizing the effort required for proper care.

---

## Features
- Real-time display of **clock** and **soil moisture level**  
- Smart, low-cost, and modular design  
- Easily expandable hardware for future enhancements  
- Structured code based on the **Power of Ten** principle for clarity and maintainability

---

## Hardware Components
| Component                       | Description                 |
|---------------------------------|-----------------------------|
| **Arduino Nano**                | Main controller board       |
| **DS1307 RTC Module**           | Real-Time Clock module      |
| **16x2 LCD**                    | Displays time and wet level |
| **Analog Soil Moisture Sensor** | Measures soil humidity      |

---

## Code & Programming
- Written in **C++** using **Object-Oriented Programming (OOP)** principles  
- Split across **three files** for better readability and modularity  
- Compatible with Arduino IDE; minor adjustments allow compilation in other environments  
- Based on the **Power of Ten** article for structured and maintainable code  

---

## How It Works
1. The **soil moisture sensor** sends an analog signal representing soil humidity to the Arduino.  
2. Arduino interprets the value to determine if the soil is **wet** or **dry**.  
3. The **DS1307 RTC module** provides the current time.  
4. The **LCD** displays both the **soil moisture** and **current time** simultaneously.

---

## How to Use
1. Connect the Arduino Nano, Tiny RTC, LCD, Sensors According and Power(5v) to the wiring diagram.  
2. Monitor the LCD for real-time soil moisture readings and current time.  
3. Optionally, adjust thresholds in the code for wet/dry soil levels.

---

## How to Make
1. Gather the required components: Arduino Nano, DS1307 RTC, 16x2 LCD, Soil Moisture Sensor.  
2. Connect the modules as shown in the schematic diagram.  
3. Install the necessary Arduino libraries (`Wire.h`, `LiquidCrystal_I2C.h`, etc.).  
4. Copy the project code into the Arduino IDE and upload to the board.  
5. Test the system by inserting the moisture sensor into the soil.  

---

## Future Improvements
- Add **Bluetooth/Wi-Fi** modules for wireless monitoring  
- Integrate **temperature & humidity sensors** (DHT11/DHT22)  
- Automate watering with **DC motor or water pump**  
- Replace the **LCD** with an **OLED display** for advanced visualization

========================================================================================================
