#include "math.h"
#include "../Position/PositionLoc.h"
#include <Arduino.h>
#include "../LegSubsystem/Constants.h"

#ifndef InverseKinematics_h
#define InverseKinematics_h

class InverseKinematics
{
public:
    // calculates the angles needed for each servo to reach a specific point in 3D space

    float calFootPos2Anchor(int16_t coord, int16_t anchor) { return coord - anchor; };

    // kneeOffset

       float calcKneeOffset(float x, float y, float coxaLen) {
        float D = sqrt(x*x + y*y);
        if (D < 0.001f) return 0;
        return coxaLen / D;
    }


    float calculateDistance(float x, float y) {
        return sqrt((x * x) + (y * y));
    }

    // law of cosines, it can be used to find either the angle of length of a side of a triangle dependent on the given information.
    float lawOfCosines(float a, float b, float c) {
        float v = (a*a + b*b - c*c) / (2 * a * b);
        v = constrain(v, -1.0f, 1.0f);  // FIX: avoid NaN
        return acos(v);
    }
};

#endif