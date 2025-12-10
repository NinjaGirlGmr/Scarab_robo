#include <Arduino.h>

#include <Wire.h>
#include "hexapod_base.h"
#include "pwm_drivers.h"
#include "Adafruit_PWMServoDriver.h"
#include "LegSubsystem/Constants.h"



HexapodBase hexapod;


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  Serial.println("PCA9685 Servo Test");

  pwmRight.begin();
  pwmRight.setPWMFreq(60);

  pwmLeft.begin();
  pwmLeft.setPWMFreq(60);

  delay(10);

  
  //hexapod.wakeup();
  

  delay(50);

}

void loop()
{
  // put your main code here, to run repeatedly:
  hexapod.zeroAllLegs(1000);
  delay(1000);
  hexapod.goToPos(-70,70,-50,20,4);
  delay(1000);
  hexapod.goToPos(-70,70,-120,20,4);
  delay(1000);
  hexapod.goToPos(-70,70,20,20,4);
  delay(1000);
  


 
}
