#include "LegSubsystem/HexServo.h"
#include "LegSubsystem/Constants.h"

void HexServo::initialize(String id, uint8_t channel, bool isInverted,bool isCoxa)
{
    m_id = id;
    m_channel = channel;
    m_isInverted = isInverted;
    isCoxaServo=isCoxa;

 
}

void HexServo::setAngle(float angle)
{
    float temp_angle;

    // Clamp angle depending on whether this is a coxa or femur/foot servo
    if (isCoxaServo)
        temp_angle = constrain(angle, coxa_minRot, coxa_manRot);
    else
        temp_angle = constrain(angle, minRot, maxRot);

    // Correct inversion BEFORE mapping to pulse width
    if (m_isInverted)
        temp_angle = -temp_angle;

    m_angle = temp_angle;

    // Now map the FINAL (possibly inverted) angle to PWM
    pulseWidth = map(
        temp_angle,
        minRot, maxRot,
        Constants::Pulse_Width_Min,
        Constants::Pulse_Width_Max
    );

    writeMicroseconds(pulseWidth);
}



void HexServo::setSpeed(uint8_t speed)
{
    this->speed = constrain(speed, Constants::min_speed, Constants::max_speed);
}

void HexServo::setFlexabilityMode(bool mode)
{
    flexabilityMode = mode;
}

float HexServo::estimateDistanceFromExtreme(float angle)
{
    float distanceFromExtreme = 0.0;
    if (angle > 0)
    {
        distanceFromExtreme = maxRot - angle;
    }
    else
    {
        distanceFromExtreme = angle - minRot;
    }
    return distanceFromExtreme;
}
