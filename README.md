# GyroVisor
A gimbal suspended north pointing visor.  It is a cardanic suspension build on a base plate, with two "rings" an outer ring, which is rotating around an axis , suspended on two bearings on the the perimeter of the ring at 180 degree. The rotation angle is controlled by an servo motor on one of the two bearings. Then in the inside of this ring there is another ring, which is also rotating, but the rotating axis is at 90 degree to the rotation axis of the outer ring. Also here the rotation angle is controlled by an servo motor on one of the two bearings. Then, in the inside of this inner ring is a motor, which can rotate freely, and it is has an encoder. On this motor axle, an round platform with an arrow (or a camera) is mounted. There is a electronic circuit, which is fixed on the base plate. So, when the base platform is mounted on a irregularly moving vehicle, gondola, vessel or airplane, the circuit is designed to control the two servo motors and the motor with encoder so that the arrow always stays horizontally, and the arrow (or camera) on the platform always points to the same direction, always compensating the movements of the airplane. This is commonly known as a "gimbal".

Circuit diagram
<img width="3000" height="3934" alt="gyrovisor" src="https://github.com/user-attachments/assets/267ae83e-ee7e-4d76-96ea-76e28eb54790" />

# Stl parts:

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/stl.zip 

# picture how the different stl parts look like 

http://raikkulenz.kapsi.fi/downloadfolder_not_protected/parts_stl.pdf 

# picture of the whole GyroVisor
http://raikkulenz.kapsi.fi/downloadfolder_not_protected/kokonaiskuva.pdf

# 3D view


<img width="481" height="495" alt="gimbal" src="https://github.com/user-attachments/assets/8aa9f2bc-c5b9-4270-953c-a2b915441136" />


# Photo

![N20-motor-TB6612FNG_bridge_photo](https://github.com/user-attachments/assets/3dac5248-ad4f-407c-a7a6-ff1216dc90db)


# demo video link

[![Watch the video](https://img.youtube.com/vi/kvSa0N7uzfM/0.jpg)]
(https://www.youtube.com/watch?v=kvSa0N7uzfM)

## Circuit Documentation

Summary

This circuit is designed to control a motor using an Arduino UNO, a TB6612FNG motor driver, and a motor with an encoder. The circuit also includes a potentiometer for input, a logic level converter, a BNO055 sensor, and a PWM servo breakout board to control servos. The Arduino UNO reads the potentiometer and encoder values to control the motor's position using a proportional control algorithm. The circuit is powered via a USB C connection.

## Component List

### Arduino UNO
Description: A microcontroller board based on the ATmega328P.
Pins: UNUSED, IOREF, Reset, 3.3V, 5V, GND, Vin, A0, A1, A2, A3, A4, A5, SCL, SDA, AREF, D13, D12, D11, D10, D9, D8, D7, D6, D5, D4, D3, D2, D1, D0.

### Trimmer Potentiometer
Description: A variable resistor used to adjust the input voltage.
Pins: leg1, wiper, leg2.
Properties: Resistance: 10,000 Ohms.

### TB6612FNG Motor Driver
Description: A motor driver used to control the motor's direction and speed.
Pins: GND, B01, B02, A02, A01, VCC, VM, PWMB, BI2, BI1, STBY, AI1, AI2, PWMA.

<img width="209" height="210" alt="TB6612FNG_picture" src="https://github.com/user-attachments/assets/1f35821a-2ae7-48b7-86bd-0179a3a10b7b" />

### Motor N20 with Encoder
Description: A small DC motor with an integrated encoder for feedback.
Pins: Red:M2, Black:VCC, Yellow:C2, Green:C1, Blue:GND, White:M1.

<img width="726" height="201" alt="N20-motor" src="https://github.com/user-attachments/assets/238b897d-e499-4351-9ce7-15d6c06e4662" />


### USB C to 2 fils
Description: A power supply interface.
Pins: USB C, +, -.
Resistor (100k Ohms)
Description: A fixed resistor used in the voltage divider.
Pins: pin1, pin2.

### Resistor (33k Ohms)
Description: A fixed resistor used in the voltage divider.
Pins: pin1, pin2.

Logic Level Converter
Description: Converts voltage levels between different components.
Pins: HV1, HV2, HV, GND, HV3, HV4, LV1, LV2, LV, LV3, LV4.

### BNO055
Description: An intelligent 9-axis absolute orientation sensor.
Pins: Vin, 3vo, GND, SDA, SCL, RST.

<img width="328" height="433" alt="BNO055_picture" src="https://github.com/user-attachments/assets/da19a43a-91b5-44ef-9ab6-82c22055d9f2" />

<img width="770" height="360" alt="BNO055-pinout" src="https://github.com/user-attachments/assets/3621b246-3d60-414e-83d5-66aa5ae3098c" />


### Micro Servo 9G
Description: A small servo motor for precise control.
Pins: GND, +5V, PWM.

### Adafruit PCA9685 PWM Servo Breakout
Description: A PWM driver board for controlling servos.
Pins: 5.0V, GND, PWRIN, PWM7, PWM6, PWM5, PWM4, PWM3, PWM2, PWM1, PWM0, VCC, SDA, SCL, OE, PWM15, PWM14, PWM13, PWM12, PWM11, PWM10, PWM9, PWM8.

<img width="718" height="414" alt="PCA9685-picture_with_explanations" src="https://github.com/user-attachments/assets/215f01b7-36d2-429c-8f6a-11c99bd26670" />


## Wiring Details

### Arduino UNO

5V connected to:

    Trimmer Potentiometer (leg2)

    Adafruit PCA9685 PWM Servo Breakout (VCC)

    Logic Level Converter (HV)

    TB6612FNG Motor Driver (VCC)

GND connected to:

    Logic Level Converter (GND)

    Motor N20 with Encoder (Blue:GND)

    TB6612FNG Motor Driver (GND)

    Adafruit PCA9685 PWM Servo Breakout (GND)

    Trimmer Potentiometer (leg1)

    D9 connected to TB6612FNG Motor Driver (STBY)

    D5 connected to TB6612FNG Motor Driver (PWMA)

    D4 connected to TB6612FNG Motor Driver (AI2)

    D10 connected to TB6612FNG Motor Driver (AI1)

    A0 connected to Trimmer Potentiometer (wiper)

    A1 connected to Resistor (pin1 of 33k Ohms)

3.3V connected to:

    BNO055 (3vo)

    Logic Level Converter (LV)

    Motor N20 with Encoder (Black:VCC)

    D3 connected to Motor N20 with Encoder (Green:C1)

    D2 connected to Motor N20 with Encoder (Yellow:C2)

A4 connected to:

    Adafruit PCA9685 PWM Servo Breakout (SDA)

    Logic Level Converter (HV4)

A5 connected to:

    Adafruit PCA9685 PWM Servo Breakout (SCL)

    Logic Level Converter (HV2)

### Trimmer Potentiometer

leg2 connected to Arduino UNO (5V)

wiper connected to Arduino UNO (A0)

leg1 connected to:

    Adafruit PCA9685 PWM Servo Breakout (OE)

    Adafruit PCA9685 PWM Servo Breakout (GND)

    Resistor (pin2 of 100k Ohms)

    Arduino UNO (GND)

### TB6612FNG Motor Driver

VCC connected to Arduino UNO (5V)

GND connected to:

    Arduino UNO (GND)

    USB C to 2 fils (-)

STBY connected to Arduino UNO (D9)

PWMA connected to Arduino UNO (D5)

AI2 connected to Arduino UNO (D4)

AI1 connected to Arduino UNO (D10)

A02 connected to Motor N20 with Encoder (Red:M2)

A01 connected to Motor N20 with Encoder (White:M1)

VM connected to:

    USB C to 2 fils (+)

    Resistor (pin1 of 100k Ohms)

### Motor N20 with Encoder

Red:M2 connected to TB6612FNG Motor Driver (A02)

White:M1 connected to TB6612FNG Motor Driver (A01)

Blue:GND connected to Arduino UNO (GND)

Black:VCC connected to Arduino UNO (3.3V)

Green:C1 connected to Arduino UNO (D3)

Yellow:C2 connected to Arduino UNO (D2)

### USB C to 2 fils

- connected to TB6612FNG Motor Driver (GND)

+ connected to TB6612FNG Motor Driver (VM)

### Resistor (100k Ohms)

pin1 connected to TB6612FNG Motor Driver (VM)

pin2 connected to Trimmer Potentiometer (leg1)

### Resistor (33k Ohms)

pin1 connected to Arduino UNO (A1)

pin2 connected to Resistor (pin1 of 100k Ohms)

### Logic Level Converter

HV connected to Arduino UNO (5V)

GND connected to Arduino UNO (GND)

LV connected to Arduino UNO (3.3V)

HV4 connected to Arduino UNO (A4)

HV2 connected to Arduino UNO (A5)

LV2 connected to BNO055 (SCL)

LV4 connected to BNO055 (SDA)

### BNO055

3vo connected to Arduino UNO (3.3V)

GND connected to Logic Level Converter (GND)

SDA connected to Logic Level Converter (LV4)

SCL connected to Logic Level Converter (LV2)

### Micro Servo 9G

GND connected to Adafruit PCA9685 PWM Servo Breakout (PWM0)

+5V connected to Adafruit PCA9685 PWM Servo Breakout (5.0V)

PWM connected to Adafruit PCA9685 PWM Servo Breakout (GND)

### Adafruit PCA9685 PWM Servo Breakout

VCC connected to Arduino UNO (5V)

GND connected to Arduino UNO (GND)

SDA connected to Arduino UNO (A4)

SCL connected to Arduino UNO (A5)

OE connected to Trimmer Potentiometer (leg1)

PWM0 connected to Micro Servo 9G (GND)

5.0V connected to Micro Servo 9G (+5V)


![Visitor Count](https://komarev.com/ghpvc/?username=ReinhardLenz&repo=GyroVisor&color=green)
