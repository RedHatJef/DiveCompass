//
// Created by redha on 2/16/2025.
//

#ifndef DIVECOMPASS_DEVICES_H
#define DIVECOMPASS_DEVICES_H

#include "Display.h"
#include "CompassBase.h"

typedef struct Devices {
    Display* display;
    CompassBase* compass;
};

#endif //DIVECOMPASS_DEVICES_H
