////
//// Created by redha on 2/15/2025.
////
//
//#include <QMC5883LCompass.h>
//#include "CompassQMC5883L.h"
//
//static QMC5883LCompass compass;
//
//CompassQMC5883L::CompassQMC5883L() { }
//
//void CompassQMC5883L::init() {
//    pinMode(3, INPUT);
//    compass.init();
//    compass.setSmoothing(10, true);
//
//
//}
//
//bool CompassQMC5883L::update() {
//    if(digitalRead(3) == 0) return false;
//
//    compass.read();
//    headingInt = compass.getAzimuth();
//    compass.getX();
//    if(headingInt < 0) headingInt += 360;
//
//    return true;
//}
//
//int CompassQMC5883L::getHeading() const { return headingInt; }
//
//void CompassQMC5883L::calibrate() {
//    compass.calibrate();
//
//    calibrationData.offset0 = compass.getCalibrationOffset(0);
//    calibrationData.offset1 = compass.getCalibrationOffset(1);
//    calibrationData.offset2 = compass.getCalibrationOffset(2);
//    calibrationData.scale0 = compass.getCalibrationScale(0);
//    calibrationData.scale1 = compass.getCalibrationScale(1);
//    calibrationData.scale2 = compass.getCalibrationScale(2);
//}
//
//double CompassQMC5883L::getYaw() const {
//    return 0;
//}
//
//double CompassQMC5883L::getPitch() const {
//    return 0;
//}
//
//double CompassQMC5883L::getRoll() const {
//    return 0;
//}
