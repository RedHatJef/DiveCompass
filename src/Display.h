//
// Created by redha on 2/16/2025.
//

#ifndef DIVECOMPASS_DISPLAY_H
#define DIVECOMPASS_DISPLAY_H


#include <stdint.h>

class Display {
public:
    Display() { }
    void init();
    void update();
    void updateFromISR();

    void beginCalibration();
    void endCalibration();

    void clear();

private:
    unsigned long calibrationStartTime;
    uint8_t lastXStart;
    uint8_t lastYStart;
    uint8_t lastXEnd;
    uint8_t lastYEnd;
};


#endif //DIVECOMPASS_DISPLAY_H
