#include "pwm_drivers.h"

// LEFT side = 0x41
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(0x41);

// RIGHT side = 0x40
Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(0x40);
