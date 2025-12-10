#include <Arduino.h>

#include "HexServo.h"
#include "../Position/PositionLoc.h"
#include "../kinematics/kinematics.h"
#include "Leg.h"
#include "../pwm_drivers.h"
#include "Constants.h"

// coodPosition

Leg::Leg(LegPosition id, int16_t anchX, int16_t anchY)
{

    m_position = id;
    m_anchorX = anchX;
    m_anchorY = anchY;
    m_anchorZ = 0;

    // when initzllizing a leg, if a leg has been met, supply it with this information based on the id
    // of the position. If its the front left leg, meet this criteria, if that not it
    // switch to the next leg
    // so on and so forth
    anchorDegOffset = atan2(anchY, anchX) * Constants::Rad_to_Deg;

    switch (id)
    {
    case LegPosition::FRONT_LEFT:
        footHexServo.initialize("LF_Foot", Constants::LFF, false,false);
        kneeHexServo.initialize("LF_Knee", Constants::LFK, true,false);
        rotHexServo.initialize("LF_Rot", Constants::LFR, false,true);
        footHexServo.attachPWM(&pwmLeft,1);
        kneeHexServo.attachPWM(&pwmLeft,1);
        rotHexServo.attachPWM(&pwmLeft,1);
        break;

    case LegPosition::FRONT_RIGHT:
        footHexServo.initialize("RF_Foot", Constants::RFF, true,false);
        kneeHexServo.initialize("RF_Knee", Constants::RFK, false,false);
        rotHexServo.initialize("RF_Rot", Constants::RFR, true,true);
        footHexServo.attachPWM(&pwmRight,0);
        kneeHexServo.attachPWM(&pwmRight,0);
        rotHexServo.attachPWM(&pwmRight,0);
        break;

    case LegPosition::MIDDLE_LEFT:
        footHexServo.initialize("RF_Foot", Constants::LMF, false,false);
        kneeHexServo.initialize("RF_Knee", Constants::LMK, true,false);
        rotHexServo.initialize("RF_Rot", Constants::LMR, false,true);
        footHexServo.attachPWM(&pwmLeft,1);
        kneeHexServo.attachPWM(&pwmLeft,1);
        rotHexServo.attachPWM(&pwmLeft,1);
        break;

    case LegPosition::MIDDLE_RIGHT:
        footHexServo.initialize("RF_Foot", Constants::RMF, true,false);
        kneeHexServo.initialize("RF_Knee", Constants::RMK, false,false);
        rotHexServo.initialize("RF_Rot", Constants::RMR, true,true);
        footHexServo.attachPWM(&pwmRight,0);
        kneeHexServo.attachPWM(&pwmRight,0);
        rotHexServo.attachPWM(&pwmRight,0);
        break;

    case LegPosition::BACK_LEFT:
        footHexServo.initialize("RF_Foot", Constants::LBF, false,false);
        kneeHexServo.initialize("RF_Knee", Constants::LBK, true,false);
        rotHexServo.initialize("RF_Rot", Constants::LBR, false,true);
        footHexServo.attachPWM(&pwmLeft,1);
        kneeHexServo.attachPWM(&pwmLeft,1);
        rotHexServo.attachPWM(&pwmLeft,1);
        break;

    case LegPosition::BACK_RIGHT:
        footHexServo.initialize("RF_Foot", Constants::RBF, true,false);
        kneeHexServo.initialize("RF_Knee", Constants::RBK, false,false);
        rotHexServo.initialize("RF_Rot", Constants::RBR, true,true);
        footHexServo.attachPWM(&pwmRight,0);
        kneeHexServo.attachPWM(&pwmRight,0);
        rotHexServo.attachPWM(&pwmRight,0);
        break;
    }
}

bool Leg::setCoordPosition(PositionLoc coodPosition, uint8_t speed)
{
    InverseKinematics ik;

    // Local relative coordinates
    float footXRel = ik.calFootPos2Anchor(coodPosition.x, m_anchorX);
    float footYRel = ik.calFootPos2Anchor(coodPosition.y, m_anchorY);
    float footZRel = ik.calFootPos2Anchor(coodPosition.z, m_anchorZ);

    float zDist = abs(footZRel);


    float hipAngle = atan2(footYRel, footXRel) * Constants::Rad_to_Deg;
    hipAngle -= anchorDegOffset;

 
    float rotS = ik.calculateDistance(footXRel, footYRel);

    if (rotS < 0.001f) rotS = 0.001f;

    float normalize = ik.calcKneeOffset(footXRel, footYRel, coxaLength);

    float kneeX = m_anchorX + footXRel * normalize;
    float kneeY = m_anchorY + footYRel * normalize;

    float kx = coodPosition.x - kneeX;
    float ky = coodPosition.y - kneeY;

    float kneeS = sqrt(kx*kx + ky*ky);


    float footS = sqrt(kneeS*kneeS + zDist*zDist);

    
    float AngleFoot = ik.lawOfCosines(femurLength, footLength, footS);
    float footAngle = AngleFoot * Constants::Rad_to_Deg - 90;  // physical offset

    float AngleB = ik.lawOfCosines(footS, femurLength, footLength);

    float AngleA = atan2(zDist, kneeS);

    float kneeAngle = (AngleA + AngleB) * Constants::Rad_to_Deg;

    if (isnan(hipAngle) || isnan(kneeAngle) || isnan(footAngle)) {
        Serial.println("IK Failed (NaN). Check geometry.");
        return false;
    }

    Serial.print("Hip: "); 
    Serial.print(hipAngle);
    Serial.print(" | Knee: ");
    Serial.print(kneeAngle);
    Serial.print(" | Foot: "); 
    Serial.println(footAngle);
    
    rotHexServo.setAngle(hipAngle);
    kneeHexServo.setAngle(kneeAngle);
    footHexServo.setAngle(footAngle);

    rotHexServo.setSpeed(speed);
    kneeHexServo.setSpeed(speed);
    footHexServo.setSpeed(speed);

    m_footX = coodPosition.x;
    m_footY = coodPosition.y;
    m_footZ = coodPosition.z;

    return true;
}

void Leg::setFlexibilityMode(bool mode)
{
    footHexServo.setFlexabilityMode(mode);
    kneeHexServo.setFlexabilityMode(mode);
    rotHexServo.setFlexabilityMode(mode);
}
