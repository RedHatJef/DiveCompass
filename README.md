# DiveCompass
Underwater dive compass for cave diving survey based on Atmel AVR128DA32

## Devices
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

| Pin | Connected To |
| :---: | --- |
| 1 | Main I2C SCL |
| 26 | Reset Switch |
| 31 | Main I2C SDA |


