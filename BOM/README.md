## Bill of Materials (BOM)

### Logic & Control
| Component | Qty | Specifications | Purpose |
| :--- | :---: | :--- | :--- |
| **Arduino Mega 2560** | 1 | ATmega2560 R3 | Main Controller (High I/O) |
| **PCA9685** | 1 | 16-Channel 12-bit PWM | Servo Driver (I2C) |
| **I2C Multiplexer** | 1 | TCA9548A (or equiv) | Addressing multiple I2C devices |

### Power System
| Component | Qty | Specifications | Purpose |
| :--- | :---: | :--- | :--- |
| **LiPo Battery** | 1 | 11.1V (3S) 4500/5200 mAh | Main Power Source |
| **XL4015 Buck Converter** | 2 | 5A High Current DC-DC | Voltage regulation for logic/servos |
| **PCT Connectors** | - | 2:6 Pole Lever-nut | Power distribution rail |

### Actuation & Motion
| Component | Qty | Specifications | Purpose |
| :--- | :---: | :--- | :--- |
| **L298N Motor Driver** | 2 | Dual H-Bridge | DC Motor Control |
| **BO Motors** | 4 | Geared Yellow Motors | Drive system |
| **MG90S Servos** | 4 | Metal Gear Micro Servo | Manipulator joints |

### Perception & Structure
| Component | Qty | Specifications | Purpose |
| :--- | :---: | :--- | :--- |
| **VL53L1X** | 1 | Time-of-Flight (ToF) | Long-range distance sensing |
| **Manipulator Chassis** | 1 | 3D Printed | Arm structure |
| **Mobile Chassis** | 1 | 4WD Plate | Main robot base |
| **Fasteners** | - | M3/M2 Screws, Nuts, Spacers | Structural assembly |


