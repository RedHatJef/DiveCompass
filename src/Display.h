#ifndef DIVECOMPASS_DISPLAY_H
#define DIVECOMPASS_DISPLAY_H

#include <stdint.h>
#include "Devices.h"

class Display {
public:
    Display() = default;
    void setup(const Devices* devices);
    void update();
    void showCalibrating(uint8_t acc0, uint8_t acc1);
    void showCalibrationSaved();

private:
    const Devices* devices;
};

#endif //DIVECOMPASS_DISPLAY_H
