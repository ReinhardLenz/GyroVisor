#include "A_servo.h"

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_MIN  120  // Min pulse length out of 4096
#define SERVO_MAX  600  // Max pulse length out of 4096
#define SERVO_PIN1 0    
#define SERVO_PIN1 1    

void initServo() {
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(10);
}
void setServoAngle0(int angle) {
  angle = constrain(angle, 0, 180);
  int pulselen = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(0, 0, pulselen);
}

void setServoAngle1(int angle) {
  angle = constrain(angle, 0, 180);
  int pulselen = map(angle, 0, 180, SERVO_MIN, SERVO_MAX);
  pwm.setPWM(1, 0, pulselen);
}
