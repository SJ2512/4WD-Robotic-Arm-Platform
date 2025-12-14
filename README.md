# 4WD Robotic Arm Platform (Phase-1 Prototype)

A mobile manipulator prototype combining a classic 4WD base with a 4-DOF robotic arm.  
This phase focused on completing the full mechatronic foundation, integrating all subsystems, and validating a working pick-and-place routine. The platform serves as the base for future autonomous and vision-guided upgrades.

## Phase-1 Achievements

### Full Mechatronic Platform
- 4WD chassis running on dual L298N drivers  
- Arduino Mega as main controller  
- Stable power system using dual buck converters + LiPo battery  
- Clean wiring with PCT connectors  

###  4-DOF Arm Working
- 4× MG90S metal gear servos  
- Controlled using PCA9685 (with I2C multiplexer)  
- Smooth motion for short-range manipulation  

###  Integrated System Demo
The robot successfully performs a **proximity-triggered fetch task**:
1. Detect object    
2. Pick it  
3. Rotate 180°  
4. Place it  

## Hardware Used

- Classic 4WD chassis  
- 4× DC motors  
- 2× L298N drivers  
- Arduino Mega  
- PCA9685 servo controller  
- I2C multiplexer 

Full list in `/bom/`.

## Phase-2 (Planned Upgrades)

- ESP32 for onboard vision  
- Object detection + autonomous pick-and-place  
- Improved arm kinematics + torque upgrade  
- Better gripper accuracy  
- Autonomous navigation  
- Cleaner modular wiring  
- Payload + stability improvements  

## Status  
**Prototype — Phase 1 Complete**  
Core platform is functional and validated. Vision and autonomy are planned for the next build cycle.
GitHub: *https://github.com/SJ2512*


