# ESP32 Robotic Arm Platform

## Overview

Custom evolution of the L-ONE Cyberbrick robotic arm platform.

This project focuses on:
- embedded control architecture
- robotic system integration
- custom electronics
- modular hardware expansion

---

## Main Modifications

### Base Joint Upgrade
Replacement of the original base motor with:
- 28BYJ-48 stepper motor
- ULN2003 driver module

### Control System
Integration of:
- ESP32 microcontroller
- PCA9685 servo controller

### Power Architecture
Integration of:
- ELEGOO MB V2 power module

---

## Hardware Architecture

```text
ESP32
 ├── PCA9685 → Servo Motors
 ├── ULN2003 → Stepper Motor
 └── WiFi/Bluetooth → Future Remote Control
```

---

## Planned Expansions

### Branch A — Linear Axis
Future implementation of a 4th axis using:
- linear rail
- GT2 belt system
- stepper motor

### Branch B — Remote Control
Future integration with:
- Makerslab Arm Robot Control App

---

## Technologies

### Embedded & Electronics
- ESP32
- PCA9685
- ULN2003
- Embedded systems

### Robotics
- Servo motors
- Stepper motors
- Robotic arm integration

### CAD & Manufacturing
- SolidWorks
- Bambu Studio
- 3D printing

---

## Current Development Status

Current progress:
- Original mechanical parts printed
- Electronic components collected and tested
- System architecture defined

Current development focuses on redesigning the base joint structure in order to:
- increase internal volume
- integrate ESP32 electronics
- integrate power distribution
- integrate PCA9685 module
- integrate stepper motor driver

The base structure will be mechanically modified by raising and hollowing the original support to create enough internal space for the embedded control system.

Future developments will include:
- linear axis expansion
- remote control integration
- wireless control architecture
