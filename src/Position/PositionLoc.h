#ifndef POSITIONLOC_H
#define POSITIONLOC_H
#include <Arduino.h>

struct PositionLoc
{
    // x pos of leg
    int16_t x;
    // y pos of leg
    int16_t y;
    // z pos of leg
    int16_t z;
};
#endif