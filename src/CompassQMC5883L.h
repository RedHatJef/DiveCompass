////
//// Created by redha on 2/15/2025.
////
//
//#ifndef DIVECOMPASS1_COMPASSQMC5883L_H
//#define DIVECOMPASS1_COMPASSQMC5883L_H
//
//#include "CompassBase.h"
//
//
//class CompassQMC5883L : public CompassBase {
//public:
//    CompassQMC5883L();
//
//    void init() override;
//    bool update() override;
//    int getHeading() const override;
//    void calibrate() override;
//
//    typedef struct CalibrationData {
//        float offset0;
//        float offset1;
//        float offset2;
//        float scale0;
//        float scale1;
//        float scale2;
//    };
//
//    double getYaw() const override;
//
//    double getPitch() const override;
//
//    double getRoll() const override;
//
//public:
//
//    CalibrationData getCalibrationData() const;
//
//private:
//    int headingInt;
//    CalibrationData calibrationData;
//
//};
//
//
//#endif //DIVECOMPASS1_COMPASSQMC5883L_H
