# **Circuit Documentation**

## **Summary**

This circuit is designed to control a motor with an encoder, two micro servos, and an inertial measurement unit (IMU) using an Arduino Due. The circuit includes a motor driver, logic level converter, and various passive components such as resistors and capacitors. Power is supplied via a USB C connector. The circuit is capable of controlling the motor and servos while reading feedback from the encoder and IMU.

## **Component List**

1. **TB6612FNG Motor Driver**  
   * Description: Motor driver for controlling DC motors.  
   * Pins: GND, B01, B02, A02, A01, VCC, VM, PWMB, BI2, BI1, STBY, AI1, AI2, PWMA  
2. **Motor N20 with Encoder**  
   * Description: DC motor with integrated encoder for feedback.  
   * Pins: Red (Motor Power \+), Black (Coding Power supply \+), Yellow (Hall signal A), Green (Hall signal B), Blue (Hall sensor power \-), White (Motor Power \-)  
3. **USB C to 2 Wires**  
   * Description: Power supply interface.  
   * Pins: USB C, \+, \-  
4. **Resistor (100k Ohms)**  
   * Description: Passive component for current limiting or voltage division.  
   * Pins: pin1, pin2  
5. **Resistor (33k Ohms)**  
   * Description: Passive component for current limiting or voltage division.  
   * Pins: pin1, pin2  
6. **Logic Level Converter**  
   * Description: Converts voltage levels between different components.  
   * Pins: HV1, HV2, HV, GND, HV3, HV4, LV1, LV2, LV, LV3, LV4  
7. **Micro Servo 9G (x2)**  
   * Description: Small servo motor for precise control.  
   * Pins: GND, \+5V, PWM  
8. **Arduino Due**  
   * Description: Microcontroller board for controlling the circuit.  
   * Pins: A0-A11, DAC0, DAC1, CANRX, CANTX, D0-D53, IOREF, MASTER-RESET, 5V, GND, VIN, AREF, SDA1, SCL1, MISO, Vcc, MOSI, SCK, Reset  
9. **BNO085**  
   * Description: Inertial Measurement Unit (IMU) for motion sensing.  
   * Pins: VCC, GND, SCL/SCK/RX, SDA/MISO/TX, ADR/MOSI, CS, INT, RST, PS1, PS0  
10. **Electrolytic Capacitor (0.1 µF) (x2)**  
    * Description: Capacitor for filtering and smoothing voltage.  
    * Pins: \-, \+  
11. **Ceramic Capacitor (0.1 µF) (x2)**  
    * Description: Capacitor for filtering and decoupling.  
    * Pins: pin0, pin1

## **Wiring Details**

### **TB6612FNG Motor Driver**

* **VCC**: Connected to Arduino Due 5V, Logic Level Converter HV, and other components.  
* **GND**: Connected to Arduino Due GND, Logic Level Converter GND, and USB C \-.  
* **STBY**: Connected to Arduino Due D9 PWM.  
* **PWMA**: Connected to Arduino Due D5 PWM.  
* **AI1**: Connected to Arduino Due D10 PWM/SS0.  
* **AI2**: Connected to Arduino Due D4 PWM/SS1.  
* **A01**: Connected to Motor N20 White (Motor Power \-).  
* **A02**: Connected to Motor N20 Red (Motor Power \+).  
* **VM**: Connected to USB C \+ and Resistor (100k Ohms) pin1.

### **Motor N20 with Encoder**

* **Red (Motor Power \+)**: Connected to TB6612FNG Motor Driver A02.  
* **White (Motor Power \-)**: Connected to TB6612FNG Motor Driver A01.  
* **Black (Coding Power supply \+)**: Connected to Arduino Due IOREF, Logic Level Converter LV, and BNO085 VCC.  
* **Blue (Hall sensor power \-)**: Connected to Arduino Due GND, Logic Level Converter GND.  
* **Yellow (Hall signal A)**: Connected to Arduino Due D2 PWM.  
* **Green (Hall signal B)**: Connected to Arduino Due D3 PWM.

### **USB C to 2 Wires**

* **\+**: Connected to TB6612FNG Motor Driver VM and Resistor (100k Ohms) pin1.  
* **\-**: Connected to TB6612FNG Motor Driver GND.

### **Resistors**

* **100k Ohms**: pin1 connected to USB C \+ and TB6612FNG Motor Driver VM; pin2 connected to Resistor (33k Ohms) pin2 and other components.  
* **33k Ohms**: pin1 connected to Arduino Due A1; pin2 connected to Resistor (100k Ohms) pin2 and other components.

### **Logic Level Converter**

* **HV**: Connected to Arduino Due 5V and other components.  
* **GND**: Connected to Arduino Due GND and other components.  
* **LV**: Connected to Arduino Due IOREF, BNO085 VCC, and Motor N20 Black (Coding Power supply \+).  
* **HV2**: Connected to Arduino Due A5.  
* **HV4**: Connected to Arduino Due A4.  
* **LV2**: Connected to BNO085 SCL/SCK/RX.  
* **LV4**: Connected to BNO085 SDA/MISO/TX.

### **Micro Servo 9G**

* **\+5V**: Connected to Arduino Due 5V and other components.  
* **GND**: Connected to Arduino Due GND and other components.  
* **PWM**: First servo connected to Arduino Due D6 PWM; second servo connected to Arduino Due D7 PWM.

### **Arduino Due**

* **5V**: Connected to TB6612FNG Motor Driver VCC, Logic Level Converter HV, and other components.  
* **GND**: Connected to TB6612FNG Motor Driver GND, Logic Level Converter GND, and other components.  
* **D9 PWM**: Connected to TB6612FNG Motor Driver STBY.  
* **D5 PWM**: Connected to TB6612FNG Motor Driver PWMA.  
* **D4 PWM/SS1**: Connected to TB6612FNG Motor Driver AI2.  
* **D10 PWM/SS0**: Connected to TB6612FNG Motor Driver AI1.  
* **D2 PWM**: Connected to Motor N20 Yellow (Hall signal A).  
* **D3 PWM**: Connected to Motor N20 Green (Hall signal B).  
* **D6 PWM**: Connected to first Micro Servo 9G PWM.  
* **D7 PWM**: Connected to second Micro Servo 9G PWM.  
* **A1**: Connected to Resistor (33k Ohms) pin1.  
* **A4**: Connected to Logic Level Converter HV4.  
* **A5**: Connected to Logic Level Converter HV2.  
* **IOREF**: Connected to Logic Level Converter LV, BNO085 VCC, and Motor N20 Black (Coding Power supply \+).

### **BNO085**

* **VCC**: Connected to Arduino Due IOREF, Logic Level Converter LV, and Motor N20 Black (Coding Power supply \+).  
* **GND**: Connected to Logic Level Converter GND.  
* **SCL/SCK/RX**: Connected to Logic Level Converter LV2.  
* **SDA/MISO/TX**: Connected to Logic Level Converter LV4.

### **Capacitors**

* **Electrolytic Capacitor (0.1 µF)**: Positive pins connected to Arduino Due 5V and other components; negative pins connected to Arduino Due GND and other components.  
* **Ceramic Capacitor (0.1 µF)**: pin0 connected to Arduino Due 5V and other components; pin1 connected to Arduino Due GND and other components.

## **Code Documentation**

There is no embedded code provided for this circuit. The Arduino Due can be programmed using the Arduino IDE to control the motor, servos, and read data from the encoder and IMU. The code should include initialization of the motor driver, servos, and IMU, as well as control logic for operating the motor and servos based on feedback from the encoder and IMU.