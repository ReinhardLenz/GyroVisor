#include <Encoder.h>
#include "Compass.h"
#include "A_servo.h"


// --------------------- TB6612 Motor Driver ---------------------
const int pwmA = 5;
const int in1A = 10;
const int in2A = 4;
const int stby = 9;

// --------------------- VM Sensing ---------------------
#define VM_SENSE A1
const float VM_DIVIDER = 4.03;   // 100k / 33k divider
const float VM_THRESHOLD = 3.5;  // volts

// --------------------- Encoder ---------------------
Encoder enc(2, 3);

// --------------------- Control Parameters ---------------------
const float Kp = 0.05;     // proportional gain
const int DEADZONE = 12;   // encoder counts tolerance
const long SCALE_DEG_TO_ENC = 33L;  
// ~12 counts per pot unit = ~12000 counts full-scale for 1023 pot units.
// 12000 counts / 360° ≈ 33 counts per degree.

// --------------------- Compass ---------------------
Compass compass;
float heading = 0.0;
float roll = 0.0;
float pitch= 0.0;
// --------------------- Runtime Variables ---------------------
long targetEnc = 0;
long currentEnc = 0;
long error = 0;
float lastHeading = 0.0;
float continuousHeading = 0.0;

// --------------------- Setup ---------------------
void setup() {
  Serial.begin(9600);
  Serial.println("BNO055 + TB6612 Encoder Control");

  // Motor control pins
  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, LOW);

  // Initialize IMU
  compass.initializeIMU();
  initServo();
  delay(1000);
}

// --------------------- Helper Functions ---------------------
float readVmVoltage() {
  int raw = analogRead(VM_SENSE);
  float vin = raw * (5.0 / 1023.0);
  return vin * VM_DIVIDER;
}

// --------------------- Main Loop ---------------------
void loop() {
  static float lastHeading = 0.0;       // stores previous IMU reading
  static float continuousHeading = 0.0; // unwrapped continuous heading

  float vm = readVmVoltage();

  if (vm > VM_THRESHOLD) {
    digitalWrite(stby, HIGH); // enable motor driver

    // Read current heading from BNO055
    heading = compass.getHeading();   // 0–360°

    // --- Compute continuous heading to avoid 0°↔360° jumps ---
    float delta = heading - lastHeading;

    // Handle wrap-around crossing (e.g., 359° → 1° gives delta = -358°, fix it)
    if (delta > 180.0) delta -= 360.0;
    else if (delta < -180.0) delta += 360.0;

    continuousHeading += delta; //continuousHeading can grow beyond 0–360° (e.g. −720°, +1440°, etc.) It represents how much total rotation has occurred.
    lastHeading = heading;

    // --- Convert continuous heading → target encoder counts ---
    targetEnc = -(long)(continuousHeading * SCALE_DEG_TO_ENC); // also targetEnc can grow beyond 11880 or lelow -11880

    // --- Read encoder ---
    currentEnc = enc.read();

    // --- Compute control error ---
    error = targetEnc - currentEnc;
    long absErr = abs(error);

    // --- Compute PWM (proportional control) ---
    int pwm = (int)(Kp * absErr);
    if (pwm > 255) pwm = 255;

    // --- Control motor direction ---
    if (absErr <= DEADZONE) {  //if it is already close enough
      analogWrite(pwmA, 0); // stop motor
      digitalWrite(in1A, LOW);
      digitalWrite(in2A, LOW);
    } else if (error > 0) {     // moto
      digitalWrite(in1A, HIGH);
      digitalWrite(in2A, LOW);
      analogWrite(pwmA, pwm);
    } else {
      digitalWrite(in1A, LOW);
      digitalWrite(in2A, HIGH);
      analogWrite(pwmA, pwm);
    }

    // --- Debug output ---
 /*
    Serial.print("VM: "); Serial.print(vm, 2);
    Serial.print("  Heading: "); Serial.print(heading, 1);
    Serial.print("  ContHead: "); Serial.print(continuousHeading, 1);
    Serial.print("  TargetEnc: "); Serial.print(targetEnc);
    Serial.print("  Enc: "); Serial.print(currentEnc);
    Serial.print("  Err: "); Serial.print(error);
    Serial.print("  PWM: "); Serial.println(pwm);
*/
  } else {
    // VM below threshold → disable motor driver
    digitalWrite(stby, LOW);
    analogWrite(pwmA, 0);
    Serial.println("VM missing, driver disabled.");
  }
    roll=compass.getRoll();
    Serial.print("roll:");
    Serial.print(roll);
    setServoAngle0(90-roll);
    
    pitch=compass.getPitch();
    Serial.print("pitch:");
    Serial.println(pitch);
    
    setServoAngle1(90-pitch);

  delay(50);




}
