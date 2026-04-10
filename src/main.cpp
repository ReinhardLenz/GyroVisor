#include <Arduino.h>
#include <SparkFun_BNO08x_Arduino_Library.h>
#include <Encoder.h>
#include "Compass.h"
#include <Wire.h>
#include <Servo.h>

#define BNO08X_RESET -1
#define TIMEOUT_BOOT_BNO 100
#define BNO08X_I2C_ADDRESS 0x4B

const int alwaysOnButtonPin = A0;
unsigned long millisOld;
const unsigned long vibrationDurationMillis = 200UL;
const unsigned long vibrationIntervalMillis = 1000UL;
const unsigned long serialKeepDurationMillis = 10UL * 1000UL;


//const int PIN_SDA = A4;   // works on many cores; otherwise set explicit pin numbers
//const int PIN_SCL = A5;

static uint32_t lastGoodEventMs = 0;
static uint32_t bootMs = 0;
static uint32_t lastRecoverAttemptMs = 0;

// Tune these:
const uint32_t STARTUP_GRACE_MS = 3000;          // wait after setup before any recovery
const uint32_t NO_EVENT_BEFORE_RECOVER_MS = 4000; // must be "dead" this long before recovery
const uint32_t RECOVER_COOLDOWN_MS = 5000;        // minimum time between recovery attempts

int degree_shift;
long lastSerialRecv = -10000L;
float lastSerialHeading = 0.0f;


Compass compass;
BNO08x imu;

#define DBG_PRINTLN(x) do { if (Serial) Serial.println(x); } while(0)
#define DBG_PRINT(x)   do { if (Serial) Serial.print(x); } while(0)


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
const int DEADZONE = 600;   // encoder counts tolerance
const long SCALE_DEG_TO_ENC = 33L;  
// ~12 counts per pot unit = ~12000 counts full-scale for 1023 pot units.
// 12000 counts / 360° ≈ 33 counts per degree.

// --------------------- Compass ---------------------
float heading = 0.0;
float roll = 0.0;
float pitch= 0.0;
// --------------------- Runtime Variables ---------------------
long targetEnc = 0;
long currentEnc = 0;
long error = 0;
float lastHeading = 0.0;
float continuousHeading = 0.0;

Servo servo_pitch;
Servo servo_roll;

//PID control  variables
float Ki = 0.0002;
float Kd = 0.01;

// PID state variables
float integral = 0;
float lastError = 0;
unsigned long lastTime = 0;


// --------------------- Helper Functions ---------------------
float readVmVoltage() {
  int raw = analogRead(VM_SENSE);
  float vin = raw * (5.0 / 1023.0);
  return vin * VM_DIVIDER;
}
// Simple function to blink the built-in LED n times (for error indication)
void blinkCode(int n) {
  for (int i = 0; i < n; i++) {
    digitalWrite(LED_BUILTIN, HIGH); delay(150);
    digitalWrite(LED_BUILTIN, LOW);  delay(150);
  }
  delay(600);
}


// --------------------- Setup ---------------------
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  // Motor control pins
  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  pinMode(stby, OUTPUT);
  digitalWrite(stby, LOW);
  //Servo initialization
  servo_pitch.attach(7);
  servo_roll.attach(6);
  delay(2000);  // give bootloader time to enumerate
  blinkCode(1);  // reached setup start
  Serial.begin(9600);
  blinkCode(2);  // reached setup start
/*

  unsigned long t0 = millis();
  bool serialReady = false;

  while (millis() - t0 < 2000) {        // Wait max 2 sec
    if (Serial) {
      serialReady = true;
      break;
    }
    delay(10);
  }


  if (serialReady) {
    Serial.println("Serial monitor connected!");
    digitalWrite(LED_BUILTIN, HIGH);    // optional indicator
  } else {
    // Serial monitor not connected, continue anyway
  }
*/
  Wire.begin();
  blinkCode(3);  // reached setup start

  Wire.setClock(10000);
  delay(300);   // IMPORTANT: let BNO085 boot 
  // Initialize IMU

// Start communication with BNO085

  int retries = 0;
  while (!imu.begin() && retries < 10) {
    blinkCode(9); // IMU begin retry marker
    delay(500);
    retries++;
  }
  blinkCode(4);  // after imu.begin loop

  if (!imu.enableGameRotationVector(50)) {
    blinkCode(7); // enable report failed
  } else {
    blinkCode(5); // enabled ok
  }
    delay(1000);
  }

// --------------------- Main Loop ---------------------
void loop() {
static bool t = false;
t = !t;
digitalWrite(LED_BUILTIN, t);

float vm = readVmVoltage();
if (vm > VM_THRESHOLD) {
  digitalWrite(stby, HIGH); // enable motor driver
  //    heading = compass.getHeading(degree_shift);   // 0–360°
  bool gotEvent = imu.getSensorEvent();
  if (gotEvent) {
    // Push the new event into Compass
    compass.updateFromSensor(imu.sensorValue);
    // Compute heading once for this event, using the latest degree_shift
    heading = compass.getHeading(degree_shift);
    lastGoodEventMs = millis();
  } else {
    // Optional 1s heartbeat
    static uint32_t lastPrintMs = 0;
    if (millis() - lastPrintMs > 1000) {
      //Serial.println("No sensor event (not necessarily an error)");
      lastPrintMs = millis();
      }
  }
  
  // --- Compute continuous heading to avoid 0°↔360° jumps ---
  float delta = heading - lastHeading;
  // Handle wrap-around crossing (e.g., 359° → 1° gives delta = -358°, fix it)
  if (delta > 180.0) delta -= 360.0;
  else if (delta < -180.0) delta += 360.0;
  continuousHeading += delta; //continuousHeading can grow beyond 0–360° (e.g. −720°, +1440°, etc.) It represents how much total rotation has occurred.
  // --- Convert continuous heading → target encoder counts ---
  targetEnc = (long)(continuousHeading * SCALE_DEG_TO_ENC); // also targetEnc can grow beyond 11880 or lelow -11880

  currentEnc = -enc.read();

  // --- Compute control error ---
  //  error = targetEnc - currentEnc;
  error = currentEnc - targetEnc;
  DBG_PRINT("Error: "); 
  DBG_PRINTLN(error);  // --- Read encoder ---

  long absErr = abs(error);
  // --- Compute PWM (proportional control) ---


 //PID control
  // --- Time step ---
  unsigned long now = millis();
  float dt = (now - lastTime) / 1000.0;  // seconds
  lastTime = now;

  // Avoid division by zero
  if (dt <= 0) dt = 0.001;

  // --- PID terms ---
  float P = error;
  integral += error * dt;

  // Anti-windup (important!)
  if (integral > 10000) integral = 10000;
  if (integral < -10000) integral = -10000;

  float derivative = (error - lastError) / dt;
  lastError = error;

  // --- PID output ---
  float output = Kp * P + Ki * integral + Kd * derivative;

  // Convert to PWM
  int pwm = abs((int)output);


  if (pwm > 255) pwm = 255;
  // --- Control motor direction ---
  if (absErr <= DEADZONE) {  //if it is already close enough
    analogWrite(pwmA, 0); // stop motor
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, LOW);
  } else if (output > 0) {     // moto
    digitalWrite(in1A, HIGH);
    digitalWrite(in2A, LOW);
    analogWrite(pwmA, pwm);

  } else {
    digitalWrite(in1A, LOW);
    digitalWrite(in2A, HIGH);
    analogWrite(pwmA, pwm);

  }

  } else {
    // VM below threshold → disable motor driver
    digitalWrite(stby, LOW);
    analogWrite(pwmA, 0);
  //    Serial.println("VM missing, driver disabled.");
}

roll = compass.getRoll();
servo_roll.write(90-roll);  

pitch = compass.getPitch();
servo_pitch.write(90+pitch);


/*
DBG_PRINT(millis());
DBG_PRINT(",");
DBG_PRINTLN(error);
*/

lastHeading = heading;
// heartbeat LED to indicate loop is alive 
digitalWrite(LED_BUILTIN, millis() % 1000 < 500);
}