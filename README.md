# 4WD Mobile Manipulator Platform (Flagship Project)

## Overview

The **4WD Mobile Manipulator Platform** is a battery-powered robotic system combining a four-wheel drive mobile base with a 4-DOF robotic arm capable of object detection and retrieval.

The project explores the integration challenges of **mobility, manipulation, and power-dense embedded systems** within a compact robotic platform. It is being developed as a long-term robotics engineering platform with future expansion into autonomous navigation, vision-based manipulation, and SLAM.

Phase-1 focuses on hardware architecture, power distribution, and basic object retrieval capability.

---

## Current Capabilities (Phase-1)

* 4WD mobile robotic base
* 4-DOF servo-based robotic manipulator
* Time-of-Flight based object detection
* Pick → rotate 180° → place routine
* Fully battery-powered onboard system

---

## Key Specifications

| Parameter        | Value                         |
| ---------------- | ----------------------------- |
| Drive System     | 4WD BO motor chassis          |
| Manipulator      | 4-DOF servo arm               |
| Payload Capacity | ~50 g                         |
| Control MCU      | Arduino Mega 2560             |
| Servo Driver     | PCA9685                       |
| Sensor           | VL53L1X ToF                   |
| Battery          | 11.1V LiPo (4500–5200 mAh)    |
| Power System     | Dual buck regulated rails     |
| Operation Mode   | Semi-autonomous demo sequence |

---

# Why this project exists

Most entry-level robotics projects isolate mobility and manipulation as separate systems.
This project was built to explore the engineering complexity that emerges when both are integrated into a single compact platform.

The long-term goal is a **mobile object retrieval robot** capable of operating in unknown or semi-structured environments.

Instead of building a stationary robotic arm or a simple mobile robot, this platform focuses on:

* Power distribution under mixed loads
* Structural stability on a moving base
* Torque vs weight trade-offs
* Multi-voltage embedded system design
* Sensor-driven manipulation

Phase-1 validates the feasibility of detecting, picking, relocating, and placing objects using a fully onboard system.

---

# System Architecture

## Electronics Stack

**Main Controller**

* Arduino Mega 2560
  Chosen for high I/O count and stable multi-device control.

**Drive System**

* 4 × BO DC motors
* 2 × L298N motor drivers (temporary)

**Manipulator**

* 4-DOF 3D printed arm
* 4 × MG90S metal gear servos
* PCA9685 servo driver for stable PWM control

**Sensors**

* VL53L1X ToF sensor for object detection
* I2C multiplexer for multi-device communication

**Power Electronics**

* 11.1V LiPo battery
* 2 × XL4015 5A buck converters
* PCT connectors for modular distribution

---

# Power Architecture (Critical Design Area)

The platform required simultaneous handling of:

* High current motor loads
* Servo peak current demands
* Noise-sensitive logic electronics

A multi-rail architecture was implemented:

| Rail         | Purpose         |
| ------------ | --------------- |
| 11.1V direct | Motor drivers   |
| 6V regulated | Servos          |
| 5V regulated | Logic & sensors |

Logic and motor power were separated to reduce:

* Voltage drops
* Electrical noise
* Microcontroller resets

While effective, wiring density became a major limitation, indicating the need for a dedicated **power distribution PCB** in future versions.

---

# Mechanical System

## Chassis

* Compact 4WD base
* BO gear motors
* Dense internal packaging

Compact size improved portability but restricted wiring and layout flexibility.

## Manipulator

* 4-DOF 3D printed structure
* MG90S servos
* Mounted directly on chassis

### Mechanical Limitation

MG90S servos produced insufficient torque to reliably lift the arm against gravity.

A temporary tension-assist mechanism using rubber supports was implemented to reduce effective load and enable lifting.

This exposed key design requirements:

* Higher torque servos
* Better weight distribution
* Metal arm structure for future versions


# Control Logic (Phase-1)

Current behavior sequence:

1. Detect object using ToF sensor
2. Position arm to pickup
3. Lift object
4. Rotate 180°
5. Place object

System currently operates as a structured semi-autonomous routine.

Planned but not yet implemented:

* Master-slave control architecture
* Sensor fusion with IMU
* Vision integration


# Observed Performance

### Stable Behaviors

* Consistent object detection
* Reliable pick-and-place sequence
* Stable voltage after rail separation
* Fully battery powered operation

### Electrical Observations

* Buck converters maintained stable output
* Logic rail isolation reduced resets
* Wiring complexity increased debugging time

### Mechanical Observations

* Payload limited to ~50 g
* Arm lift performance torque-limited
* Compact chassis complicated maintenance


# Where it breaks (Engineering Limits)

## Electronics & Power

* L298N drivers inefficient and waste power
* Initial Li-ion pack caused voltage sag
* Dense wiring reduced serviceability
* No central power distribution board

## Mechanical

* MG90S torque insufficient
* Arm stability affected by weight distribution
* Compact chassis restricted upgrades

## Drive System

* BO motors inconsistent under load
* Torque drop during simultaneous arm + drive


# Lessons Learned

* Power distribution determines overall stability
* Cheap motor drivers drastically reduce efficiency
* Servo torque must be calculated against arm length and load
* Wiring architecture becomes critical in multi-voltage systems
* Mobile manipulators amplify both mechanical and electrical constraints

---

# Future Development (Phase-2 & 3)

## Electronics & Control

* Replace L298N with BTS7960 drivers
* Dedicated power distribution PCB
* Raspberry Pi + camera integration
* MPU6050 orientation tracking
* Master-slave architecture

## Autonomy

* Vision-based object detection
* LiDAR integration
* SLAM navigation
* ROS-based control

## Mechanical

* Higher torque servos
* Aluminium arm structure
* Custom larger chassis
* Improved payload capacity

---

# Engineering Design Decisions

## Why Arduino Mega 2560?

The system required simultaneous control of:

* Multiple servos
* Motor drivers
* I2C sensors
* Expansion capability

Arduino Uno-class boards were insufficient in I/O and memory.
Arduino Mega was selected for:

* High GPIO availability
* Stable multi-device control
* Rapid prototyping reliability
* Easy future expansion to master–slave architecture

---

## Why LiPo battery over Li-ion pack?

Initial testing with Li-ion cells resulted in:

* Voltage drop under load
* Reduced motor torque
* Unstable performance during simultaneous drive + arm operation

LiPo battery was selected due to:

* Higher discharge capability
* Stable voltage under peak current
* Better suitability for robotics load profiles

This significantly improved overall system stability.

---

## Why dual buck converter architecture?

The system required multiple voltage rails:

* Logic (5V)
* Servos (~6V)
* Motors (battery rail)

A dual buck architecture was implemented to:

* Isolate noise-sensitive logic circuits
* Prevent MCU resets during motor spikes
* Provide stable servo voltage
* Reduce electrical interference

This separation improved reliability but increased wiring complexity, leading to plans for a dedicated power distribution PCB in future revisions.

---

## Why PCA9685 servo driver?

Direct servo control from MCU caused:

* Timing instability
* Potential jitter under multi-servo load

PCA9685 provided:

* Stable hardware PWM generation
* Reduced MCU load
* Cleaner servo control
* Expandability for future DOF increase

---

## Why L298N used despite inefficiency?

L298N drivers were used temporarily due to:

* Immediate availability
* Rapid prototyping needs
* Simplicity of integration

However, testing revealed:

* High power loss
* Heat generation
* Reduced motor efficiency

Future versions will replace L298N with BTS7960 high-current drivers.
---
