#ifndef DIVECOMPASS_DEVICES_H
#define DIVECOMPASS_DEVICES_H

#include "CompassBNO08X.h"

typedef struct Devices {
    CompassBNO08X* compass0;
    CompassBNO08X* compass1;
};

#endif //DIVECOMPASS_DEVICES_H
