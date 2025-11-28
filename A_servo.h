#ifndef SERVO_H
#define SERVO_H

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h> // Library PCA9685 driver

// Initializes the PCA9685 driver
void initServo();

// Sets servo to a specific angle (0–180 degrees)
void setServoAngle0(int angle);
void setServoAngle1(int angle);

#endif
