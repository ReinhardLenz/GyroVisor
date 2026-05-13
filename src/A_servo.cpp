#include "A_servo.h"

Adafruit_PWMServoDriver pca9685  = Adafruit_PWMServoDriver();

#define SERVO_MIN  120  // Min pulse length out of 4096
#define SERVO_MAX  600  // Max pulse length out of 4096
//#define SERVO_PIN1 0    
//#define SERVO_PIN1 1    

void initServo() {
  pca9685.begin();
  pca9685.setPWMFreq(60);
  delay(10);
}
void setServoAngle0(int angle) {
  angle = constrain(angle, 0, 180);
  int pulselen = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pca9685.setPWM(0, 0, pulselen);
}

void setServoAngle1(int angle) {
  angle = constrain(angle, 0, 180);
  int pulselen = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pca9685.setPWM(1, 0, pulselen);
}
