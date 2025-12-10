#ifndef interperlation_h
#define interperlation_h
#include "../LegSubsystem/Constants.h"
#include "../Position/PositionLoc.h"
class inerperlation
{
    // to create procedural easing through the procedural walk.

    // y=x
    //  x is seen as our starting track, no easing or intererlation
    //  y is the modifide track, it should start and end at the same
    //  place as x, functioning as an eqivilant to x

    // pos + f&v + z&a
    // y + k1y'+k2y''=x+k3x'

    // frequency
    // k1 =z/pif

    // zeta = dammpener, tell program to settle, greater than 1, wont vibrate
    // k2 = 1/(2pif)^2

    // r = response, if r is greater than 1, will overshoot, when -, will anticipate
    // k3= rz/2pif

    // base with semi-implicit euler method

private:
    float f = Constants::f;
    float zeta = Constants::zeta;
    float r = Constants::r;

public:
    inerperlation() {}

    // calculate the target position based on the current position, frequency, damping, and response
    // this is a placeholder for the actual interperlation logic
    // it should take the current position, frequency, damping, and response
    PositionLoc calCurrentPOS(PositionLoc currentPosition)
    {
        // apply the interperlation logic here
        // for now, just return the current position
        return PositionLoc{currentPosition.x, currentPosition.y, currentPosition.z};
    }

    // calculate the target position based on the current position, frequency, damping, and response
    PositionLoc calcTargetPOS(PositionLoc currentPosition, PositionLoc targetPosition)
    {
        // apply the interperlation logic here
        // for now, just return the target position
        return PositionLoc{targetPosition.x, targetPosition.y, targetPosition.z};
    }
};

#endif