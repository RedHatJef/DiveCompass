//
// Created by redha on 2/16/2025.
//

#ifndef DIVECOMPASS_DISPLAY_H
#define DIVECOMPASS_DISPLAY_H

#include <stdint.h>

class Display {
public:
    Display() = default;
    void init();
    void update();
    void updateFromISR();

    void beginCalibration();
    void endCalibration();

    void clear();
    void speedTest();

private:
    unsigned long calibrationStartTime = 0;
    uint8_t lastXStart = 0;
    uint8_t lastYStart = 0;
    uint8_t lastXEnd = 0;
    uint8_t lastYEnd = 0;
    uint8_t testRow = 0;
    bool testWhite = true;
};


#endif //DIVECOMPASS_DISPLAY_H
