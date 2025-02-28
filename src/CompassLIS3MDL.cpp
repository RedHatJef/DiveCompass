////
//// Created by redha on 2/15/2025.
////
//
//#include <Arduino.h>
//#include <avr/io.h>
//#include <LIS3MDL.h>
//#include "CompassLIS3MDL.h"
//
//LIS3MDL mag;
//
//CompassLIS3MDL::CompassLIS3MDL() { }
//
//int CompassLIS3MDL::getHeading() const { return headingInt; }
//double CompassLIS3MDL::getPitch() const { return pitch; }
//double CompassLIS3MDL::getRoll() const { return roll; }
//double CompassLIS3MDL::getYaw() const { return yaw; }
//
//void CompassLIS3MDL::init() {
//    if (!mag.init())
//    {
//        Serial.println(F("Failed to detect and initialize magnetometer!"));
//        while(1) delay(1);
//    }
//
//    pinMode(2, INPUT);
//    mag.enableDefault();
//}
//
//bool CompassLIS3MDL::update() {
//    if(digitalRead(2) == 0) return false;
//
//    mag.read();
//
//    auto x = mag.m.x;
//    auto y = mag.m.y;
//    auto z = mag.m.z;
//
//
//    double headingRads = atan((y * 1.0) / x);
//    if(headingRads < 0) headingRads += PI;
//    const double convertRads = (360.0 / PI);
//    heading = headingRads * convertRads;
//    headingInt = (int)lround(heading);
//
//    return true;
//}
//
//void CompassLIS3MDL::calibrate() {
//
//}
