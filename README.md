# GyroVisor
A gimbal suspended north pointing visor.  It is a cardanic suspension build on a base plate, with two "rings" an outer ring, which is rotating around an axis , suspended on two bearings on the the perimeter of the ring at 180 degree. The rotation angle is controlled by an servo motor on one of the two bearings. Then in the inside of this ring there is another ring, which is also rotating, but the rotating axis is at 90 degree to the rotation axis of the outer ring. Also here the rotation angle is controlled by an servo motor on one of the two bearings. Then, in the inside of this inner ring is a motor, which can rotate freely, and it is has an encoder. On this motor axle, an round platform with an arrow (or a camera) is mounted. There is a electronic circuit, which is fixed on the base plate. So, when the base platform is mounted on a irregularly moving vehicle, gondola, vessel or airplane, the circuit is designed to control the two servo motors and the motor with encoder so that the arrow always stays horizontally, and the arrow (or camera) on the platform always points to the same direction, always compensating the movements of the airplane. This is commonly known as a "gimbal".

Circuit diagram
<img width="2924" height="3459" alt="circuit_image" src="https://github.com/user-attachments/assets/7d61bd40-0775-4eac-85df-3004be9a0a3a" />


# Stl parts:

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/stl.zip 

# picture how the different stl parts look like 

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/parts_stl.pdf 

# picture of the whole GyroVisor
http://raikkulenz.kapsi.fi/downloadfolder_not_protected/kokonaiskuva.pdf

# 3D view


<img width="481" height="495" alt="gimbal" src="https://github.com/user-attachments/assets/8aa9f2bc-c5b9-4270-953c-a2b915441136" />


# Photo

![photo_BNO085_gyrovisor](https://github.com/user-attachments/assets/4bdfa9e9-6c2b-40f2-9a14-a70920be1cfe)


# demo video link

[![Demo video](https://img.youtube.com/vi/y0DqdKf1gtM/0.jpg)](https://www.youtube.com/watch?v=y0DqdKf1gtM)



# **Circuit Documentation**

## **Summary**

This circuit is designed to control a motor using an Arduino UNO, a TB6612FNG motor driver, and a motor with an encoder. The circuit also includes a potentiometer for input, a logic level converter, a BNO055 sensor, and a PWM servo breakout board to control servos. The Arduino UNO reads the potentiometer and encoder values to control the motor's position using a proportional control algorithm. The circuit is powered via a USB C connection.

## **Component List**

1. **Trimmer Potentiometer**  
   * **Description**: A variable resistor used to adjust voltage levels.  
   * **Properties**: Resistance of 10,000 Ohms.  
2. **TB6612FNG Motor Driver**  
   * **Description**: A dual motor driver used to control the direction and speed of motors.  
3. **Motor N20 with Encoder**  
   * **Description**: A small DC motor with an integrated encoder for feedback on motor position and speed.  
4. **USB C to 2 Wires**  
   * **Description**: Provides power to the circuit from a USB C source.  
5. **Resistor (100k Ohms)**  
   * **Description**: A passive component used to limit current flow.  
6. **Resistor (33k Ohms)**  
   * **Description**: Another passive component used to limit current flow.  
7. **Logic Level Converter**  
   * **Description**: Converts voltage levels between different components to ensure compatibility.  
8. **Micro Servo 9G (2 units)**  
   * **Description**: Small servos used for precise control of mechanical movements.  
9. **Arduino Due**  
   * **Description**: A microcontroller board based on the Atmel SAM3X8E ARM Cortex-M3 CPU.  
10. **BNO085**  
    * **Description**: A sensor module used for orientation and motion tracking.

## **Wiring Details**

### **Trimmer Potentiometer**

* **leg1**: Connected to GND (common ground with servos and Arduino Due).  
* **wiper**: Connected to A0 on the Arduino Due.  
* **leg2**: Connected to \+5V (common power with servos, logic level converter, and motor driver).

### ---

**TB6612FNG Motor Driver**

* **GND**: Connected to common ground with Arduino Due and motor.  
* **VCC**: Connected to \+5V (common power).  
* **VM**: Connected to the positive wire from USB C and pin1 of a 100k Ohm resistor.  
* **STBY**: Connected to D9 PWM on the Arduino Due.  
* **PWMA**: Connected to D5 PWM on the Arduino Due.  
* **AI1**: Connected to D10 PWM/SS0 on the Arduino Due.  
* **AI2**: Connected to D4 PWM/SS1 on the Arduino Due.  
* **A01**: Connected to the White:M1 pin of the motor.  
* **A02**: Connected to the Red:M2 pin of the motor.

### ---

**Motor N20 with Encoder**

* **Red:M2**: Connected to A02 on the motor driver.  
* **White:M1**: Connected to A01 on the motor driver.  
* **Black:VCC**: Connected to LV on the logic level converter and IOREF on the Arduino Due.  
* **Blue:GND**: Connected to common ground.  
* **Green:C1**: Connected to D3 PWM on the Arduino Due.  
* **Yellow:C2**: Connected to D2 PWM on the Arduino Due.

### ---

**USB C to 2 Wires**

* **\+**: Connected to VM on the motor driver and pin1 of a 100k Ohm resistor.  
* **\-**: Connected to GND on the motor driver.

### ---

**Resistor (100k Ohms)**

* **pin1**: Connected to VM on the motor driver and \+ wire from USB C.  
* **pin2**: Connected to pin1 of a 33k Ohm resistor.

### ---

**Resistor (33k Ohms)**

* **pin1**: Connected to pin2 of a 100k Ohm resistor.  
* **pin2**: Connected to leg1 of the trimmer potentiometer and common ground.

### ---

**Logic Level Converter**

* **HV**: Connected to \+5V (common power).  
* **GND**: Connected to common ground.  
* **LV**: Connected to VCC of BNO085 and Black:VCC of the motor.  
* **HV4**: Connected to A4 on the Arduino Due.  
* **HV2**: Connected to A5 on the Arduino Due.  
* **LV2**: Connected to SCL/SCK/RX of BNO085.  
* **LV4**: Connected to SDA/MISO/TX of BNO085.

### ---

**Micro Servo 9G**

* **GND**: Connected to common ground.  
* **\+5V**: Connected to \+5V (common power).  
* **PWM**:  
  * First servo connected to A8 on the Arduino Due.  
  * Second servo connected to A9 on the Arduino Due.

### ---

**Arduino Due**

* **5V**: Connected to \+5V (common power).  
* **GND**: Connected to common ground.  
* **IOREF**: Connected to LV on the logic level converter.  
* **A0**: Connected to the wiper of the trimmer potentiometer.  
* **A1**: Connected to pin1 of a 33k Ohm resistor.  
* **A4**: Connected to HV4 on the logic level converter.  
* **A5**: Connected to HV2 on the logic level converter.  
* **D9 PWM**: Connected to STBY on the motor driver.  
* **D5 PWM**: Connected to PWMA on the motor driver.  
* **D4 PWM/SS1**: Connected to AI2 on the motor driver.  
* **D10 PWM/SS0**: Connected to AI1 on the motor driver.  
* **D3 PWM**: Connected to Green:C1 of the motor.  
* **D2 PWM**: Connected to Yellow:C2 of the motor.  
* **A8**: Connected to PWM of the first micro servo.  
* **A9**: Connected to PWM of the second micro servo.

### ---

**BNO085**

* **VCC**: Connected to LV on the logic level converter.  
* **GND**: Connected to GND on the logic level converter.  
* **SCL/SCK/RX**: Connected to LV2 on the logic level converter.  
* **SDA/MISO/TX**: Connected to LV4 on the logic level converter.

## **Code Documentation**

The Arduino Due is programmed to control the motor driver, read encoder feedback, and manage the servos and sensor data. The logic level converter ensures proper voltage levels between the Arduino and the BNO085 sensor. 

![Visitor Count](https://komarev.com/ghpvc/?username=ReinhardLenz&repo=GyroVisor&color=green)
