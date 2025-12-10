#include <Arduino.h>
#include "math.h"
#ifndef CONSTANTS_H
#define CONSTANTS_H

class Constants
{
public:
    // servo based constants
    static const float m_manRot = 90;
    static const float m_minRot = -90;

    static const float coxa_minRot=-60;
    static const float coxa_manRot= 60;

    static const float deadban = 0.05;
    static const uint8_t min_speed = 0;
    static const uint8_t max_speed = 100;

    static const uint16_t Pulse_Width_Min = 500;  // the shortest pulse sent to a servo
    static const uint16_t Pulse_Width_Max = 2500; // the longest
    static const uint16_t Pulse_Width_Center = (Pulse_Width_Min + Pulse_Width_Max) / 2;

    // leg based constants

    // leg lengths mm
    static const float foot_length = 160;
    static const float femur_length = 111;
    static const float coxa_length = 35;

    static const float Rad_to_Deg = 180 / M_PI;

    // front legs
    // front Left
    static const int LFF = 2;
    static const int LFK = 1;
    static const int LFR = 0;
    // front right
    static const int RFF = 2;
    static const int RFK = 1;
    static const int RFR = 0;

    // middle left
    static const int LMF = 6;
    static const int LMK = 5;
    static const int LMR = 4;
    // middle right
    static const int RMF = 6;
    static const int RMK = 5;
    static const int RMR = 4;

    // back left
    static const int LBF = 10;
    static const int LBK = 9;
    static const int LBR = 8;
    // back right
    static const int RBF = 10;
    static const int RBK = 9;
    static const int RBR = 8;

    // leg constraints(x,rot offset)

    static const int LFX = 0;
    static const int LMX = 0;
    static const int LBX = 0;

    static const int RFX = 0;
    static const int RMX = 0;
    static const int RBX = 0;

    // leg constraints(y,rot offset)
    static const int LFY = 0;
    static const int LMY = 0;
    static const int LBY = 0;

    static const int RFY = 0;
    static const int RMY = 0;
    static const int RBY = 0;

    // gryo based constants

    // math based constants + procedural

    static const float f = 2.33;
    static const float zeta = 0.5;
    static const float r = 0.45;

    static const int16_t min_home_h = -40;   // foot z/height from body, (should probably make this a tiny bit lower than home)
    static const int16_t max_home_h = -140;   // foot z/height from body
    static const int16_t home_h = 0;       // home height for foot
    static const int16_t sleep_mode_h = 0; // height of leg from body when robot is asleep
};

#endif // CONSTANTS_H