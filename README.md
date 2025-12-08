# 4WD Robotic Arm Platform (Phase-1 Prototype)

A mobile manipulator prototype combining a classic 4WD base with a 4-DOF robotic arm.  
This phase focused on completing the full mechatronic foundation, integrating all subsystems, and validating a working pick-and-place routine. The platform serves as the base for future autonomous and vision-guided upgrades.

---

## 🚀 Phase-1 Achievements

### ✔ Full Mechatronic Platform
- 4WD chassis running on dual L298N drivers  
- Arduino Mega as main controller  
- Stable power system using dual buck converters + LiPo battery  
- Clean wiring with PCT connectors  

### ✔ 4-DOF Arm Working
- 4× MG90S metal gear servos  
- Controlled using PCA9685 (with I2C multiplexer)  
- Smooth motion for short-range manipulation  

### ✔ Integrated System Demo
The robot successfully performs a **proximity-triggered fetch task**:
1. Detect object  
2. Approach  
3. Pick it  
4. Rotate 180°  
5. Place it  

Video in `/demo/pick-and-place.mp4`.

---

## 🧩 Hardware Used

- Classic 4WD chassis  
- 4× DC motors  
- 2× L298N drivers  
- Arduino Mega  
- PCA9685 servo controller  
- I2C multiplexer  
- 4× MG90S servos (arm)  
- 2× buck converters  
- LiPo battery  
- PCT connectors  

Full list in `/bom/bom.txt`.

---

## 🖼 Media

Images located in `/images/`:
- main.jpg  
- arm.jpg  
- chassis.jpg  
- wiring.jpg  

Demo video in `/demo/`.

---

## 📂 Repo Structure

