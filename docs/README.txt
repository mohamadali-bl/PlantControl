* Plant Monitoring 🪴
* Arduino Based Soil Moisture System

## English Description:

### Overview
The **Plant Monitor** project is designed to simplify the maintenance of indoor and house plants.  
It measures (soil moisture) and displays both (time) and (moisture level) on a 16x2 character LCD.  
This helps users take better care of their plants with minimal effort.

---

### Features
- Real-time display of clock and soil moisture
- Smart and low-cost design for easy plant care
- Modular and easily expandable hardware
- Code structured based on the "Power of Ten" principle for clarity and maintainability

---

### Hardware Components
Arduino Nano == Main controller board 
DS1307 RTC Module == Real-time clock module 
16x2 LCD Module == display for showing data
Soil Moisture Sensor == Sensor to measure soil humidity

---

### Code and Programming
The code of this project is written in C++ based on object-oriented programming(OOP). The program has three files for ease, greater readability execution of program. 
It can be tested, programmed, and compiled in the Arduino IDE program environment, but with some changes it can also be compiled in other environments. Based on the article written by "Power Of Ten", for more information, read the said article.

---

### How It Works
1. The soil moisture sensor sends an analog signal representing the soil’s humidity level to the Arduino.  
2. Arduino reads the value and interprets whether the soil is wet or dry.  
3. The DS1307 RTC module provides the current time.  
4. The **LCD** displays both the **moisture level** and **current time** simultaneously.

---

### Future Improvements
You can easily modify this project to include:
- (Bluetooth/Wi-Fi) modules for wireless data transmission  
- Temperature & humidity sensors (DHT11/DHT22)
- (DC motor/water pump) for automatic watering  
- (OLED display) instead of the character LCD  
 

---

## توضیحات فارسی

### معرفی
پروژه‌ی نگهداری گیاه با هدف سهولت در نگهداری گیاهان آپارتمانی طراحی شده است.  
این سیستم با استفاده از **سنسور رطوبت خاک**، میزان رطوبت را اندازه‌گیری کرده و در کنار آن **ساعت جاری** را روی نمایشگر LCD کاراکتری نشان می‌دهد.  
هدف اصلی، کمک به نگهداری بهتر گیاه با حداقل تلاش کاربر است.

---

### ویژگی‌ها
- نمایش زنده‌ی زمان و رطوبت خاک 
- طراحی ساده، هوشمند و کم‌هزینه  
- قابلیت توسعه و افزودن ماژول‌های بیشتر  
- ساختار کد بر پایه‌ی اصل مقاله ده قدرت است برای خوانایی و نگهداری بهتر  

---

### اجزای سخت‌افزاری
| ماژول / قطعه | توضیحات |
|---------------|----------|
| **Arduino Nano** | برد اصلی و کنترل‌کننده‌ی پروژه |
| **DS1307 RTC Module** | ماژول ساعت واقعی |
| **LCD 16x2 Character** | نمایشگر داده‌های ساعت و رطوبت |
| **Analog Soil Moisture Sensor** | سنسور اندازه‌گیری رطوبت خاک |

---

### کد و برنامه‌نویسی 
کد این پروژه بر اساس شی گرایی در زبان سی پلاس پلاس نوشته شده است
برنامه دارای سه فایل برای سهولت ، خوانایی بیشتر و انجام سریعتر برنامه میباشد
در فضای برنامه آردوینو ای دی ای تست ، پروگرام و کامپایل پذیر است اما با تغییراتی در محیط های دیگر نیز قابل کامپایل است
بر اساس مقاله ده قدرت نوشته است ، برای اطلاعات بیشتر مقاله گفته شده را مطالعه فرمایید

---

### نحوه‌ی کارکرد
1. سنسور رطوبت مقدار رطوبت خاک را به‌صورت آنالوگ به آردوینو ارسال می‌کند.  
2. آردوینو مقدار دریافتی را خوانده و وضعیت خاک (مرطوب / خشک) را تعیین می‌کند.  
3. ماژول DS1307 زمان فعلی را فراهم می‌کند.  
4. نمایشگر LCD مقدار **رطوبت خاک** و **ساعت جاری** را به‌صورت هم‌زمان نمایش می‌دهد.  

---

### توسعه‌های پیشنهادی
با تغییرات کوچک در کد یا اتصالات، می‌توان امکانات زیر را به پروژه اضافه کرد:
- افزودن ماژول **Bluetooth / WiFi** برای انتقال بی‌سیم داده‌ها  
- افزودن سنسور **دما و رطوبت هوا (DHT11/DHT22)**  
- کنترل **پمپ آب یا موتور آرمیچر** برای آبیاری خودکار  
- استفاده از **نمایشگر OLED** به‌جای LCD   
