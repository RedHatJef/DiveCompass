//
// Created by redha on 2/15/2025.
//

#ifndef DIVECOMPASS1_COMPASSBASE_H
#define DIVECOMPASS1_COMPASSBASE_H

class CompassBase {
public:
    CompassBase() = default;

    virtual void init() = 0;
    virtual bool update() = 0;
    virtual void calibrate() = 0;

    [[nodiscard]] virtual int getHeading() const = 0;
    [[nodiscard]] virtual double getYaw() const = 0;
    [[nodiscard]] virtual double getPitch() const = 0;
    [[nodiscard]] virtual double getRoll() const = 0;
};


#endif //DIVECOMPASS1_COMPASSBASE_H
