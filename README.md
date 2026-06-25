# ESP32 Robotic Arm Platform

## Overview

Custom evolution of the L-ONE Cyberbrick robotic arm platform.

<p align="center">
  <a href="images/Robot_overview.jpeg">
    <img src="images/Robot_overview.jpeg" width="350">
    <img src="images/Robot_overview_2.jpeg" width="350">
  </a>
</p>


This project combines mechanical redesign, electronics integration and custom ESP32 firmware to create a fully wireless desktop robotic platform.

Version 1.0 is completed.

---

## Main Modifications

### Mechanical Improvements

Compared to the original L-ONE Cyberbrick design, several modifications were introduced:

- Enlarged fixed base.
- Enlarged rotating base.
- Internal compartment created for electronics integration.
- Bearing support added to the base to improve stability and load distribution.
- Replacement of the original base drive system with a 28BYJ-48 stepper motor and ULN2003 driver.
- Redesigned rotating cover with screw and nut fastening for improved rigidity and easier maintenance.
- Completely redesigned Joint 1 servo support.
- Joint 1 servo is now independently mounted using dedicated fastening screws.
- Modified worm gear assemblies to allow internal locking screws.
- Reinforced the most critical mechanical areas using screw fasteners to improve robustness and reliability.
- External ELEGOO power module with integrated ON/OFF switch.

<p align="center">
  <a href="images/Adattatore_Elego.png">
    <img src="images/Adattatore_Elego.png" width="200">
    <img src="images/Base_Rotante.png" width="200">
    <img src="images/supporto_servo_arm_1.png" width="150">
    <img src="images/Cuscinetto_base.jpeg" width="200">
  </a>
</p>
---

## Electronics Integration

Integrated components:

- ESP32 microcontroller
- PCA9685 servo controller
- ULN2003 stepper driver
- ELEGOO MB V2 power supply module

All electronics are housed inside the enlarged rotating base.

<p align="center">
  <a href="images/electronic_overview.jpeg">
    <img src="images/electronic_overview.jpeg" width="250"  >
  </a>
</p>

---

## Software Architecture

Custom firmware developed for ESP32.

Features:

- Local WiFi Access Point
- Embedded Web Server
- Browser-based control interface
- HTML + CSS + JavaScript frontend
- LittleFS filesystem integration

Development environment:

- Arduino IDE
- LittleFS uploader plugin
<p align="center">
  <a href="images/Web_page.png">
    <img src="images/Web_page.png" width="700" >
  </a>
</p>
---

## Hardware Architecture

```text
ESP32
 ├── PCA9685 → Servo Motors
 ├── ULN2003 → Stepper Motor
 ├── LittleFS → Web Interface
 └── WiFi → Browser Control
```

---

## Technologies

### Embedded & Electronics

- ESP32
- PCA9685
- ULN2003
- LittleFS
- Embedded systems

### Software

- Arduino Framework
- HTML
- CSS
- JavaScript

### Robotics

- Servo motors
- Stepper motors
# ESP32 Robotic Arm Platform

<p align="center">
  <img src="images/robot_overview.png" width="700">
</p>

## Overview

This project is a custom evolution of the **L-ONE Cyberbrick Desktop Robotic Arm**.

Instead of simply assembling the original model, the project focused on redesigning the mechanical structure, integrating new electronics and developing custom firmware based on an ESP32 microcontroller.

The final result is a compact desktop robotic arm featuring an upgraded mechanical design, integrated electronics and a browser-based control interface over a local WiFi network.

---

## Highlights

- 🤖 Custom mechanical redesign
- ⚡ ESP32-based control system
- 🌐 Browser-based WiFi interface
- 🎛️ PCA9685 servo controller
- ⚙️ Stepper motor upgrade for the base joint
- 🏗️ Integrated electronics compartment
- 🖨️ Ready-to-print CAD and Bambu Studio files
- 📚 Complete project documentation

---

## Mechanical Improvements

Compared to the original L-ONE Cyberbrick design, several modifications were introduced.

### Base Assembly

- Enlarged fixed base
- Enlarged rotating base
- Internal compartment designed to house all electronics
- Bearing support added to improve rotation stability
- External ELEGOO MB V2 power module with integrated ON/OFF switch

### Base Joint

- Original motor replaced by a **28BYJ-48 stepper motor**
- ULN2003 driver integration
- Custom stepper mounting bracket

### Joint 1

- Completely redesigned servo support
- Servo is no longer integrated into the cover
- Independent screw-mounted structure
- Improved accessibility for maintenance

### Mechanical Reinforcement

Several critical structural points have been redesigned using screw fasteners instead of relying solely on the original printed joints.

This solution increases:

- structural rigidity
- maintenance accessibility
- long-term mechanical reliability

### Worm Gear Improvements

The original worm gears were modified to include internal locking screws, improving torque transmission and preventing unwanted movement.

---

## Electronics Integration

The rotating base has been redesigned to integrate all control electronics inside the robot.

Integrated hardware:

- ESP32
- PCA9685 Servo Driver
- ULN2003 Stepper Driver
- ELEGOO MB V2 Power Module

The result is a much cleaner design with all electronics protected inside the rotating base.

---

## Software Architecture

Custom firmware was developed for the ESP32.

Main features:

- Local WiFi Access Point
- Embedded Web Server
- Browser-based user interface
- Servo control
- Stepper motor control
- LittleFS filesystem
- HTML / CSS / JavaScript frontend

Development environment:

- Arduino IDE
- LittleFS uploader plugin

---

## Hardware Architecture

```text
                   Browser
                      │
                WiFi Connection
                      │
                   ESP32
          ┌───────────┴───────────┐
          │                       │
      PCA9685                 ULN2003
          │                       │
   Servo Motors          Stepper Motor
```

---

## Technologies

### Embedded Systems

- ESP32
- Arduino Framework
- PCA9685
- ULN2003
- LittleFS

### Software

- HTML
- CSS
- JavaScript

### Mechanical Design

- SolidWorks
- Bambu Studio
- 3D Printing

### Robotics

- Servo Motors
- Stepper Motors
- Mechanical Design
- Embedded Integration

---

## Repository Structure

```text
cad/
│
├── 3mf_files/
├── solidworks/

firmware/

images/

web_interface/
```

---

## Project Status

✅ Version 1.0 Completed

Completed features:

- Mechanical redesign
- Electronics integration
- ESP32 firmware
- Embedded web interface
- CAD documentation
- Ready-to-print Bambu Studio files

---

## Future Development

### Branch A — Linear Axis

Future implementation of a fourth linear axis using:

- Linear rail
- GT2 transmission
- Stepper motor

### Branch B — Mobile Control

Future integration with:

- Makerslab Arm Robot Control App

---

## Gallery

Project images are available inside the **images** folder.

Additional assembly pictures, electronics details and software screenshots will be added in future updates.

---

## Acknowledgements

This project is based on the original **L-ONE Cyberbrick Desktop Robotic Arm**.

The repository documents all the custom mechanical, electronic and software modifications developed during this project.
