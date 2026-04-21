#ifndef DIVECOMPASS1_COMPASSBNO08X_H
#define DIVECOMPASS1_COMPASSBNO08X_H

#include <SparkFun_BNO08x_Arduino_Library.h>

class CompassBNO08X {
public:
    CompassBNO08X() = default;

    void init(uint8_t addr, int intPin, int rstPin);
    bool update();
    void calibrate();
    bool saveCalibration();

    double  getHeading()     const;
    double  getYaw()         const;
    double  getPitch()       const;
    double  getRoll()        const;
    uint8_t getMagAccuracy() const;

private:
    void setReports();

    BNO08x  myIMU;
    uint8_t _sh2Slot = 0;

    uint8_t magAccuracy = 0;
    float   yaw   = 0;
    float   pitch = 0;
    float   roll  = 0;
    double  heading = 0;
};

#endif //DIVECOMPASS1_COMPASSBNO08X_H
