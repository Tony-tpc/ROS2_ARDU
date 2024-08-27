/***************************************************************
   Motor driver definitions

   Add a "#elif defined" block to this file to include support
   for a particular motor driver.  Then add the appropriate
   #define near the top of the main ROSArduinoBridge.ino file.

   *************************************************************/

#ifdef USE_BASE

#ifdef POLOLU_VNH5019
/* Include the Pololu library */
#include "DualVNH5019MotorShield.h"

/* Create the motor driver object */
DualVNH5019MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController()
{
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd)
{
  if (i == LEFT)
    drive.setM1Speed(spd);
  else
    drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#elif defined POLOLU_MC33926
/* Include the Pololu library */
#include "DualMC33926MotorShield.h"

/* Create the motor driver object */
DualMC33926MotorShield drive;

/* Wrap the motor driver initialization */
void initMotorController()
{
  drive.init();
}

/* Wrap the drive motor set speed function */
void setMotorSpeed(int i, int spd)
{
  if (i == LEFT)
    drive.setM1Speed(spd);
  else
    drive.setM2Speed(spd);
}

// A convenience function for setting both motor speeds
void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#elif defined L298P_MOTOR_DRIVER
void initMotorController()
{
  pinMode(LEFT_DIR, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_DIR, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
}

void setMotorSpeed(int i, int spd)
{
  unsigned char reverse = 0;

  if (spd < 0)
  {
    spd = -spd;
    reverse = 1;
  }
  if (spd > 255)
  {
    spd = 255;
  }
  if (i == LEFT)
  {
    if (spd == 0)
    {
      digitalWrite(LEFT_DIR, LOW);
      return ;
    }

    digitalWrite(LEFT_DIR, HIGH);
    if (reverse == 0)
    {
      analogWrite(LEFT_PWM, 127 + spd / 2);
    }
    else if (reverse == 1)
    {
      analogWrite(LEFT_PWM, 127 - spd / 2);
    }
  }
  else /*if (i == RIGHT) //no need for condition*/
  {
    if (spd == 0)
    {
      digitalWrite(RIGHT_DIR, LOW);
      return;
    }

    digitalWrite(RIGHT_DIR, HIGH);

    if (reverse == 0)
    {
      analogWrite(RIGHT_PWM, 127 + spd / 2);
    }
    else if (reverse == 1)
    {
      analogWrite(RIGHT_PWM, 127 - spd / 2);
    }
  }
}

void setMotorSpeeds(int leftSpeed, int rightSpeed)
{
  setMotorSpeed(LEFT, leftSpeed);
  setMotorSpeed(RIGHT, rightSpeed);
}
#else
#error A motor driver must be selected!
#endif

#endif
