#ifndef Leg_h
#define Leg_h

#include <Arduino.h>
#include "Constants.h"
#include "HexServo.h"
#include "../Position/PositionLoc.h"

enum class LegPosition
{
    FRONT_LEFT,
    FRONT_RIGHT,
    MIDDLE_LEFT,
    MIDDLE_RIGHT,
    BACK_LEFT,
    BACK_RIGHT
};
class Leg
{

private:
    LegPosition m_position;
    int16_t m_anchorX = 0;
    int16_t m_anchorY = 0;
    int16_t m_anchorZ = 0;
    int16_t anchorDegOffset = 0;

    HexServo footHexServo; // foot HexServo (horn)
    HexServo kneeHexServo; // knee HexServo (femur)
    HexServo rotHexServo;  // rotation HexServo (coxa) = controls rotation from body.

    // foot corrdinates, where the tip of the foot is related to in global space of the foot
    int16_t m_footX = 0;
    int16_t m_footY = 0;
    int16_t m_footZ = 0;

    // how long each segment of the leg is, we need this to calulate inverse kinematics
    const int16_t coxaLength = Constants::coxa_length;
    const int16_t femurLength = Constants::femur_length;
    const int16_t footLength = Constants::foot_length;

    // helpful to convert all of our radions to degrees
    const float radToDeg = Constants::Rad_to_Deg;

    // the HexServos should be flexiable in their degrees, allowing a smooth stop and bouce, rather than a suddon stop.
    // idea is simular to principals of suspension in cars and animation logic.
    const bool isFlexabilityMode = false;

    bool isWalkingMode = false;

    uint8_t pwmChannel = 0;

public:
    /// @brief initializes the leg with its id and and choring position

    Leg(LegPosition position, int16_t anchorX, int16_t anchorY);

    // determines if the entire leg is in flexability mode
    // meaning it will overshoot a bit for smoother motion
    // or act like a suspenion system.
    void setFlexibilityMode(bool mode);

    // returns the foot posisition and signals where the foot is in 3D space
    PositionLoc getCoordPosition() { return PositionLoc{m_footX, m_footY, m_footZ}; }

    // return HexServos in the leg
    HexServo getFootHexServo() { return footHexServo; }
    HexServo getKneeHexServo() { return kneeHexServo; }
    HexServo getRotHexServo() { return rotHexServo; }

    /// @brief Set the position of the leg in 3D space using coordinates
    /// returns if the position is valid and can be set, or if the position is out of reach/ illegal
    bool setCoordPosition(PositionLoc coodPosition, uint8_t speed);

    // zeros motors
    void zeroAll(uint8_t speed)
    {
        // Set all HexServos to zero angle
        footHexServo.setAngle(0);
        kneeHexServo.setAngle(0);
        rotHexServo.setAngle(0);

        // Set speed for all HexServos
        footHexServo.setSpeed(speed);
        kneeHexServo.setSpeed(speed);
        rotHexServo.setSpeed(speed);
    }

    void identifyLegID(uint8_t speed)
    {
        // set the pos
        rotHexServo.setAngle(10);
        kneeHexServo.setAngle(10);
        footHexServo.setAngle(10);
        // set the speed
        rotHexServo.setSpeed(speed);
        kneeHexServo.setSpeed(speed);
        footHexServo.setSpeed(speed);
    }

    void setIsWalkingMode(bool mode)
    {
        isWalkingMode = mode;
    }

    void extremeAllLegs(int8_t deg){
        footHexServo.setAngle(deg);
        kneeHexServo.setAngle(deg);
        rotHexServo.setAngle(deg);
    }
};

#endif