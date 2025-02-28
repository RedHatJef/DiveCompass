//
// Created by redha on 2/15/2025.
//

#ifndef DIVECOMPASS1_COMPASSBNO08X_H
#define DIVECOMPASS1_COMPASSBNO08X_H

#include "CompassBase.h"

class CompassBNO08X : public CompassBase {
public:
    CompassBNO08X() = default;

    void init() override;
    bool update() override;
    void calibrate() override;

    [[nodiscard]] int getHeading() const override;
    [[nodiscard]] double getYaw() const override;
    [[nodiscard]] double getPitch() const override;
    [[nodiscard]] double getRoll() const override;

private:
    void setReports();

    float mx;
    float my;
    float mz;
    byte magAccuracy;
    float quatI;
    float quatJ;
    float quatK;
    float quatReal;
};


#endif //DIVECOMPASS1_COMPASSBNO08X_H
