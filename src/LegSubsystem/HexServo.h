#include <Arduino.h>

#include "Constants.h"
#include "../Adafruit_PWMServoDriver.h"



#ifndef Servo_H
#define Servo_H
class HexServo
{

private:
    // what is the motor id
    String m_id = "";
    // is it flipped,
    // this isn't refering to the leg to the body
    // this is the leg to itself
    // if two motors fact the same direction, one needs to be inverted
    bool m_isInverted = false;
    uint8_t speed = Constants::min_speed;
    float minRot = Constants::m_minRot;
    float maxRot = Constants::m_manRot;

    float coxa_minRot = Constants::coxa_minRot;
    float coxa_manRot = Constants::coxa_manRot;

    uint16_t pulseWidth = Constants::Pulse_Width_Center;

    // can the servo use flexability mode
    // a mode that means it can over over shoot a bit
    // simular to car suspsension or animation easing logic
    bool flexabilityMode = false;

    uint8_t m_channel = 0;

    // get angle

    float m_angle = 0.0;

    //

    bool isCoxaServo = false;
   

public:
    // intializes the servo class and its information when called

    Adafruit_PWMServoDriver* driver=nullptr;   // <--- NEW
    uint8_t driverID=0;                  // 0 = right, 1 = left


    void initialize(String id, uint8_t m_channel, bool isInverted = false, bool isCoxa=false);

    // tells the servo what angle we want
    void setAngle(float angle);

    // tells the servo what speed we want
    void setSpeed(uint8_t speed);

    void setFlexabilityMode(bool mode);

    // returns the ID of the servo
    String getID() const { return m_id; }
    // returns the channel of the servo
    uint8_t getChannel() const { return m_channel; }
    // returns the angle of the servo
    float returnTargetAngle() const { return m_angle; }
    // if the moto is or is not inverted
    bool isInverted() const { return m_isInverted; }
    // return angle position from its ectreme limits
    float estimateDistanceFromExtreme(float angle);

    void attachPWM(Adafruit_PWMServoDriver* drv, uint8_t drvID)
    {
        driver = drv;
        driverID = drvID;
    }

    void writeMicroseconds(uint16_t us)
    {
        pulseWidth = us;
        if (driver) {
            driver->writeMicroseconds(m_channel, us);
        }
    }


};

#endif