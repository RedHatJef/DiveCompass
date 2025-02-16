# DiveCompass
Underwater dive compass for cave diving survey based on Atmel AVR128DA32

## Devices
* [AVR128DA32](https://ww1.microchip.com/downloads/en/DeviceDoc/40002183A.pdf)
  * [Pinout](https://cdn.tindiemedia.com/images/resize/2fxPFlhMai_0tOqyeikwEtcKKMA=/p/fit-in/1370x912/filters:fill(fff)/i/77443/products/2023-04-18T07%3A53%3A42.799Z-DA32.png?1681779270)
* [GC9A01](https://www.makerfabs.com/desfile/files/GC9A01A.pdf) Round Display
  * SPI interface
  * May want to look for a module with backlight controls?
  * [Amazon Link](https://www.amazon.com/gp/product/B0C1G92F2B) $6
* [LIS3MDL](https://www.st.com/resource/en/datasheet/lis3mdl.pdf)
  * Magnetometer
  * Not used - very noisy and inaccurate
  * [Amazon Link](https://www.amazon.com/gp/product/B071VS6GJM)
* [MPU6050](https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf)
  * Accelerometer/Gyro
  * Not used - drift makes this unusable
  * [Amazon Link](https://www.amazon.com/gp/product/B01DK83ZYQ)
* [QMC5883L](https://www.lcsc.com/datasheet/lcsc_datasheet_2410121532_QST-QMC5883L_C976032.pdf)
  * 3-Axis Magnetic Sensor
  * Library provides good smoothing and seems to sit at +/- 0.5 degrees
  * Calibration is easy
  * [Amazon Link](https://www.amazon.com/gp/product/B008V9S64E) $7
* [BNO080](https://cdn.sparkfun.com/assets/1/3/4/5/9/BNO080_Datasheet_v1.3.pdf)
  * 9-axis sensor module
  * Accelerometer/Gyroscope/Magnetometer
  * [Amazon Link](https://www.amazon.com/gp/product/B0CDGZMLPP) $19
  

## AVR128DA32 Pin Connections

| Pin | Name | Connected To |
| ---: | :---: | :--- |
| 1 | SCL0 | Main I2C SCL |
| 2 | MOSI0 | Display SDA |
| 3 | | 
| 4 | SCK0 | Display SCL |
| 5 | SS0 | Display CS |
| 6 | GPIO | Display DC |
| 7 | | 
| 8 | | 
| 9 | | 
| 10 | | 
| 11 | | 
| 12 | | 
| 13 | | 
| 14 | | 
| 15 | | 
| 16 | | 
| 17 | | 
| 18 | AVCC | +3.3V | 
| 19 | GND | GND | 
| 20 | | 
| 21 | | 
| 22 | | 
| 23 | | 
| 24 | | 
| 25 | | 
| 26 | RST | Reset Switch |
| 27 | UPDI | Programmer UPDI |
| 28 | VCC | +3.3V | 
| 29 | GND | GND | 
| 30 | TXD0 | 220 ohm --> RS232 RXD |
| 31 | RXD0 | 220 ohm --> RS232 TXD |
| 32 | SDA0 | Main I2C SDA |


