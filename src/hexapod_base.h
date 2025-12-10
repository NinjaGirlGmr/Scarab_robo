#include "Arduino.h"
#include "math.h"
#include "LegSubsystem/LegStructure.h"
#include "Position/interperlation.h"
#include "Position/LocationOfLeg.h"
#include "Position/PositionLoc.h"
#include "Adafruit_PWMServoDriver.h"

// make leg objects

//                                      rot offset
Leg LFrontLeg(LegPosition::FRONT_LEFT, Constants::LFX, Constants::LFY);
Leg RFrontLeg(LegPosition::FRONT_RIGHT, Constants::RFX, Constants::RFY);
Leg LMiddleLeg(LegPosition::MIDDLE_LEFT, Constants::LMX, Constants::LMY);
Leg RMiddleLeg(LegPosition::MIDDLE_RIGHT, Constants::RMX, Constants::RMY);
Leg LBackLeg(LegPosition::BACK_LEFT, Constants::LBX, Constants::LBY);
Leg RBackLeg(LegPosition::BACK_RIGHT, Constants::RBX, Constants::RBY);

Leg *allLegs[6] = {&LFrontLeg, &RFrontLeg, &LMiddleLeg, &RMiddleLeg, &LBackLeg, &RBackLeg};

// hexapod base class
class HexapodBase
{
public:
    // array of all legs in the hexapod
    Leg **legs = allLegs;
    const uint8_t legCount = 6;
    // interperlation object for procedural movement
    inerperlation interperter; //<- helps to plot key frames and smooth motion

    // constructor for Hexapod Base
    HexapodBase() {}

    // sleep mode for hexapod
    // place motors into a sleeping posisiton
    void sleep() {}

    // when starting program, wakeup hexapod
    // place motors into a standing position
    void wakeup()
    {

        legs[0]->setCoordPosition(PositionLoc{30, 30, Constants::home_h}, 10);
        legs[1]->setCoordPosition(PositionLoc{30, -30, Constants::home_h}, 10);
        legs[2]->setCoordPosition(PositionLoc{0, 30, Constants::home_h}, 10);
        legs[3]->setCoordPosition(PositionLoc{0, -30, Constants::home_h}, 10);
        legs[4]->setCoordPosition(PositionLoc{-30, 30, Constants::home_h}, 10);
        legs[5]->setCoordPosition(PositionLoc{-30, -30, Constants::home_h}, 10);
    }

    // zero all legs
    void zeroAllLegs(uint8_t speed)
    {
        for (uint8_t i = 0; i < legCount; i++)
        {
            legs[i]->zeroAll(speed);
            
        }
    }
    void extremeAllLegs(int8_t deg)
    {
        for (uint8_t i = 0; i < legCount; i++)
        {
            legs[i]->extremeAllLegs(deg);
        }
    }
    // identify all legs
    void identifyLegs(uint8_t speed)
    {
        for (uint8_t i = 0; i < legCount; i++)
        {
            legs[i]->identifyLegID(speed);
        }
    }

    void goToPos( int8_t x, int8_t y, int8_t z, uint8_t speed, int8_t legid){
        
        legs[legid]->setCoordPosition(PositionLoc{x, y, z}, speed);
        
    }

    // what is required for a procedural walk cycle?
    // understaning of local space of each leg
    // understanding of global space of the hexapod
    // understanding of timing and leg phase
    // understanding of gait types and how to apply them
    // understanding of interperlation to smooth motion <- interperter object should hold math for this

    // procedural walk should be able to take in a direction from a controller
    // and apply the direction to the hexapod's movement

    // also using sensitivity from gyroscope to help stabilize movement
    // additonally scaling from center of joystick to speed of movement

    // if directional input gets stoppped early, finish step but interperlate to a stop
    // decelrate to a stop rather than a suddon stop

    // use flexability mode to determine if their is a suddon stop or a smooth stop
};