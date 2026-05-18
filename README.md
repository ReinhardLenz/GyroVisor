# GyroVisor
A gimbal suspended north pointing visor.  It is a cardanic suspension build on a base plate, with two "rings" an outer ring, which is rotating around an axis , suspended on two bearings on the the perimeter of the ring at 180 degree. The rotation angle is controlled by an servo motor on one of the two bearings. Then in the inside of this ring there is another ring, which is also rotating, but the rotating axis is at 90 degree to the rotation axis of the outer ring. Also here the rotation angle is controlled by an servo motor on one of the two bearings. Then, in the inside of this inner ring is a motor, which can rotate freely, and it is has an encoder. On this motor axle, an round platform with an arrow (or a camera) is mounted. There is a electronic circuit, which is fixed on the base plate. So, when the base platform is mounted on a irregularly moving vehicle, gondola, vessel or airplane, the circuit is designed to control the two servo motors and the motor with encoder so that the arrow always stays horizontally, and the arrow (or camera) on the platform always points to the same direction, always compensating the movements of the airplane. This is commonly known as a "gimbal".

Circuit diagram
![Diagram](images/circuit_image_PCA9685.png)


# Stl parts:

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/stl.zip 

# picture how the different stl parts look like 

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/parts_stl.pdf 




# Shopping list link collection

https://linktr.ee/Gyrovisor_gimbal

# **Circuit Documentation**

## **Summary**

This circuit is designed to control a motor using an Arduino UNO, a TB6612FNG motor driver, and a motor with an encoder. The circuit also includes a logic level converter, a BNO055 sensor, and a PWM servo breakout board to control servos. The Arduino UNO reads the encoder values to control the motor's position using a proportional control algorithm. The circuit is powered via a USB C connection.

## **Component List**

1. **TB6612FNG Motor Driver**  
   * **Description**: Dual H-Bridge motor driver for controlling motor speed and direction.  
   * **Pins**: GND, B01, B02, A02, A01, VCC, VM, PWMB, BI2, BI1, STBY, AI1, AI2, PWMA  
2. **USB C to 2 fils**  
   * **Description**: Provides power supply to the circuit.  
   * **Pins**: USB C, \+, \-  
3. **Resistor (33k Ohms)**  
   * **Description**: Used for voltage division or current limiting.  
   * **Pins**: pin1, pin2  
4. **Micro Servo 9G**  
   * **Description**: Small servo motor for precise control of angular position.  
   * **Pins**: GND, \+5V, PWM  
5. **BNO085**  
   * **Description**: 9-axis sensor for orientation and motion detection.  
   * **Pins**: VCC, GND, SCL/SCK/RX, SDA/MISO/TX, ADR/MOSI, CS, INT, RST, PS1, PS0  
6. **Electrolytic Capacitor (0.0001 Farads)**  
   * **Description**: Used for smoothing voltage fluctuations.  
   * **Pins**: \-, \+  
7. **Seeeduino XIAO**  
   * **Description**: Compact microcontroller board based on the SAMD21.  
   * **Pins**: A0 \- D0 \- DAC, A1 \- D1, A2 \- D2, A3 \- D3, A4 \- D4 \- SDA, A5 \- D5 \- SCL, A6 \- D6 \- TX, 5V, GND, 3V3, A10 \- D10 \- MOSI, A9 \- D9 \- MISO, A8 \- D8 \- SCK, A7 \- D7 \- RX  
8. **Resistor (100k Ohms)**  
   * **Description**: Used for voltage division or current limiting.  
   * **Pins**: pin1, pin2  
9. **PCA9685 Breakout Board**  
   * **Description**: 16-channel PWM driver for controlling servos and LEDs.  
   * **Pins**: GND, Output Enable, SCL, SDA, VCC, V+ (Not used), Out0 to Out15, V+0 to V+15, GND0 to GND15, A0 to A5, GND-O, OE-O, SCL-O, SDA-O, VCC-O, V+-0 (NOT USED), V+-IN, GND-IN, AO+ to A5+  
10. **Motor N20 with Encoder**  
    * **Description**: Small DC motor with built-in encoder for feedback.  
    * **Pins**: Red:M2:Red power supply positive pole :Motor Power \+, Black:VCC:Hall sensor power positive pole:Coding Power supply \+, Yellow:C2:Hall signal A:feedback signal, Green:C1:Hall signal B:feedback signal, Blue:GND:Hall sensor power negative pole, White:M1:White power supply negative pole:Motor Power \-

## ---

**Wiring Details**

### **TB6612FNG Motor Driver**

* **GND**: Connected to the common ground.  
* **VCC**: Connected to the 3.3V power rail.  
* **VM**: Connected to the positive terminal of the USB power supply and the electrolytic capacitor.  
* **STBY**: Connected to the Seeeduino XIAO pin A8 \- D8 \- SCK.  
* **PWMA**: Connected to the Seeeduino XIAO pin A6 \- D6 \- TX.  
* **AI1**: Connected to the Seeeduino XIAO pin A7 \- D7 \- RX.  
* **AI2**: Connected to the Seeeduino XIAO pin A3 \- D3.  
* **A01**: Connected to the White:M1 pin of the motor N20.  
* **A02**: Connected to the Red:M2 pin of the motor N20.

### **USB C to 2 fils**

* **\+**: Connected to the positive terminal of the electrolytic capacitor and the VM pin of the TB6612FNG Motor Driver.  
* **\-**: Connected to the common ground.

### **Resistor (33k Ohms)**

* **pin1**: Connected to the Seeeduino XIAO pin A1 \- D1.  
* **pin2**: Connected to the common ground.

### **Micro Servo 9G**

* **PWM**: Connected to the PCA9685 Breakout Board pin Out0.  
* **\+5V**: Connected to the PCA9685 Breakout Board pin V+0.  
* **GND**: Connected to the PCA9685 Breakout Board pin GND0.

### **BNO085**

* **VCC**: Connected to the 3.3V power rail.  
* **GND**: Connected to the common ground.  
* **SCL/SCK/RX**: Connected to the PCA9685 Breakout Board pin SCL and the Seeeduino XIAO pin A5 \- D5 \- SCL.  
* **SDA/MISO/TX**: Connected to the PCA9685 Breakout Board pin SDA and the Seeeduino XIAO pin A4 \- D4 \- SDA.  
* **ADR/MOSI**: Connected to the 3.3V power rail.

### **Electrolytic Capacitor**

* **\+**: Connected to the positive terminal of the USB power supply and the VM pin of the TB6612FNG Motor Driver.  
* **\-**: Connected to the common ground.

### **Seeeduino XIAO**

* **3V3**: Connected to the 3.3V power rail.  
* **GND**: Connected to the common ground.  
* **A0 \- D0 \- DAC**: Connected to the Yellow:C2 pin of the motor N20.  
* **A1 \- D1**: Connected to pin1 of the 33k Ohms resistor.  
* **A2 \- D2**: Connected to the Green:C1 pin of the motor N20.  
* **A3 \- D3**: Connected to the AI2 pin of the TB6612FNG Motor Driver.  
* **A4 \- D4 \- SDA**: Connected to the SDA pin of the PCA9685 Breakout Board and the BNO085.  
* **A5 \- D5 \- SCL**: Connected to the SCL pin of the PCA9685 Breakout Board and the BNO085.  
* **A6 \- D6 \- TX**: Connected to the PWMA pin of the TB6612FNG Motor Driver.  
* **A7 \- D7 \- RX**: Connected to the AI1 pin of the TB6612FNG Motor Driver.  
* **A8 \- D8 \- SCK**: Connected to the STBY pin of the TB6612FNG Motor Driver.

### **Resistor (100k Ohms)**

* **pin1**: Connected to the positive terminal of the USB power supply.  
* **pin2**: Connected to pin2 of the 33k Ohms resistor.

### **PCA9685 Breakout Board**

* **VCC**: Connected to the 3.3V power rail.  
* **GND**: Connected to the common ground.  
* **SCL**: Connected to the BNO085 and the Seeeduino XIAO pin A5 \- D5 \- SCL.  
* **SDA**: Connected to the BNO085 and the Seeeduino XIAO pin A4 \- D4 \- SDA.  
* **Out0**: Connected to the PWM pin of the Micro Servo 9G.  
* **V+0**: Connected to the \+5V pin of the Micro Servo 9G.  
* **GND0**: Connected to the GND pin of the Micro Servo 9G.

### **Motor N20 with Encoder**

* **Red:M2**: Connected to the A02 pin of the TB6612FNG Motor Driver.  
* **Black:VCC**: Connected to the 3.3V power rail.  
* **Yellow:C2**: Connected to the Seeeduino XIAO pin A0 \- D0 \- DAC.  
* **Green:C1**: Connected to the Seeeduino XIAO pin A2 \- D2.  
* **Blue:GND**: Connected to the common ground.  
* **White:M1**: Connected to the A01 pin of the TB6612FNG Motor Driver.

## ---

## **Code Documentation**

The Seeeduino XIAO is programmed to control the motor driver, read encoder feedback, and manage the servos and sensor data. The logic level converter ensures proper voltage levels between the Arduino and the BNO085 sensor. The code integrates motor positioning, servo actuation, and orientation sensing into a single real‑time control loop.
The Compass class handles all orientation processing from the BNO085. Incoming quaternion data from various SH2 sensor report types (Rotation Vector, Game Rotation Vector, and Gyro‑Integrated Rotation Vector) is converted into Euler angles using quaternion mathematics. The class updates yaw, pitch, and roll values and provides convenience functions for computing heading relative to magnetic north. The conversion logic uses trigonometric functions to derive Euler angles and supports both radians and degrees.
In the main program, the Seeeduino XIAO initializes the motor driver (TB6612FNG) and monitors its supply voltage through a resistor divider. It reads the rotary encoder to track the motor’s current position and compares it with a continuously integrated heading that represents total rotation. A proportional  and differential controller converts position error into PWM output to drive the motor forwards or backwards. A dead‑zone prevents unnecessary oscillation when the motor is near its target.
The BNO085 IMU is polled for new orientation data; when new sensor events arrive, the Compass class updates its internal state. Pitch and roll values are used to position two servos, allowing the system to physically reflect the sensor’s orientation. The loop runs continuously, coordinating motor control, orientation tracking, and servo movement to maintain synchronized and smooth operation.

## **Libraries used**

  sparkfun/SparkFun BNO08x Cortex Based IMU@^1.0.6
  arduino-libraries/Servo@^1.3.0


## **Testing**


The python program called protocoling_error.py was used to make a diagram of the error between target and measured  encoder value.

![Diagram](images/error_time_protocol_graphical_2nd.png)

Such a protocol can be used to optimize the PID parameters.

## **Ursina visualization**

The python program called imu_visualizer.py  was used to generate a stylized 3D model of the device on the screen to verify the correctness of the IMU sensor signals. You can see it in the YouTube demo video linked above. To do this, the currently commented-out command lines inside Compass.cpp (74-79), /* Serial.print("X: "); Serial.print(ypr_1.yaw); etc., must be enabled (i.e., the /* */ must be removed), and other Serial.print commands may need to be disabled.


![Visitor Count](https://komarev.com/ghpvc/?username=ReinhardLenz&repo=GyroVisor&color=green)
