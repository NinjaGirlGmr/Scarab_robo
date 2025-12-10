#ifndef LocationOfLeg_h
#define LocationOfLeg_h
#include <Arduino.h>
#include "PositionLoc.h"

// notifys to the mation the location of each leg in 3D space
struct LocationOfLeg
{
    PositionLoc LFront;
    PositionLoc LMiddle;
    PositionLoc LBack;
    PositionLoc RFront;
    PositionLoc RMiddle;
    PositionLoc RBack;
};
#endif