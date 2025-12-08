#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_VL53L1X.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver();
Adafruit_VL53L1X tof = Adafruit_VL53L1X();

// I2C Multiplexer
#define TCA_ADDR 0x70
#define TOF_CHANNEL 1
#define PCA9685_CHANNEL 7

// Servo pins
#define SHOULDER_PIN 12
#define ELBOW_PIN    15
#define WRIST_PIN    14
#define GRIPPER_PIN  13

// Servo settings
#define SERVO_FREQ 50
#define SERVOMIN  150
#define SERVOMAX  600

// Detection range (mm)
#define DETECT_MIN 120
#define DETECT_MAX 130

// Movement speed (ms per degree)
#define SPEED_SHOULDER 50
#define SPEED_GRIPPER 30

// Current positions
struct {
  int shoulder = 125;
  int elbow = 0;
  int wrist = 100;
  int gripper = 60;
} arm;

bool isPickingUp = false;
unsigned long lastCheckTime = 0;
#define CHECK_INTERVAL 200  // Check ToF every 200ms

void tca_select(uint8_t ch) {
  if (ch > 7) return;
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Auto Pickup Arm - Initializing...");
  Wire.begin();

  // Init ToF
  tca_select(TOF_CHANNEL);
  if (!tof.begin()) {
    Serial.println("ERROR: ToF sensor failed!");
    while(1) delay(100);
  } else {
    Serial.println("ToF sensor ready.");
    tof.startRanging();
  }
  
  // Init PCA9685
  tca_select(PCA9685_CHANNEL);
  pca.begin();
  pca.setPWMFreq(SERVO_FREQ);
  Serial.println("PCA9685 ready.");
  
  // Set initial position
  Serial.println("Moving to initial position...");
  setServo(SHOULDER_PIN, arm.shoulder);
  setServo(ELBOW_PIN, arm.elbow);
  setServo(WRIST_PIN, arm.wrist);
  setServo(GRIPPER_PIN, arm.gripper);
  
  delay(1500);
  Serial.println("\n=== SYSTEM READY ===");
  Serial.println("Waiting for object at 120-130mm...\n");
}

void loop() {
  // Check ToF sensor periodically
  if (!isPickingUp && millis() - lastCheckTime >= CHECK_INTERVAL) {
    lastCheckTime = millis();
    
    tca_select(TOF_CHANNEL);
    if (tof.dataReady()) {
      uint16_t distance = tof.distance();
      tof.clearInterrupt();
      
      // Print distance for debugging
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" mm");
      
      // Check if object is in range
      if (distance >= DETECT_MIN && distance <= DETECT_MAX) {
        Serial.println("\n>>> OBJECT DETECTED! Starting pickup...\n");
        isPickingUp = true;
        pickupSequence();
        isPickingUp = false;
        Serial.println("\n>>> Pickup complete. Waiting for next object...\n");
        delay(2000); // Wait before detecting again
      }
    }
  }
  
  // Optional: Manual trigger via serial
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'p' || c == 'P') {
      Serial.println("Manual pickup triggered!");
      isPickingUp = true;
      pickupSequence();
      isPickingUp = false;
    }
  }
}


void moveServo(uint8_t pin, int target, int speed) {
  tca_select(PCA9685_CHANNEL);
  target = constrain(target, 0, 180);
  
  int start = getAngle(pin);
  int step = (target > start) ? 1 : -1;
  
  for (int angle = start; angle != target; angle += step) {
    pca.setPWM(pin, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
    delay(speed);
  }
  
  setServo(pin, target);
}

// Set servo immediately
void setServo(uint8_t pin, int angle) {
  tca_select(PCA9685_CHANNEL);
  angle = constrain(angle, 0, 180);
  pca.setPWM(pin, 0, map(angle, 0, 180, SERVOMIN, SERVOMAX));
  
  // Update state
  if (pin == SHOULDER_PIN) arm.shoulder = angle;
  else if (pin == ELBOW_PIN) arm.elbow = angle;
  else if (pin == WRIST_PIN) arm.wrist = angle;
  else if (pin == GRIPPER_PIN) arm.gripper = angle;
}

// Get current angle
int getAngle(uint8_t pin) {
  if (pin == SHOULDER_PIN) return arm.shoulder;
  if (pin == ELBOW_PIN) return arm.elbow;
  if (pin == WRIST_PIN) return arm.wrist;
  if (pin == GRIPPER_PIN) return arm.gripper;
  return 0;
}

// Pickup sequence
void pickupSequence() {
  Serial.println("  1. Moving shoulder forward (125° -> 150°)...");
  moveServo(SHOULDER_PIN, 150, SPEED_SHOULDER);
  delay(500);
  
  Serial.println("  2. Opening gripper (60° -> 120°)...");
  moveServo(GRIPPER_PIN, 120, SPEED_GRIPPER);
  delay(500);
  
  Serial.println("  3. Closing gripper to grab (120° -> 60°)...");
  moveServo(GRIPPER_PIN, 60, SPEED_GRIPPER);
  delay(500);
  
  Serial.println("  4. Bringing object back (150° -> 125°)...");
  moveServo(SHOULDER_PIN, 125, SPEED_SHOULDER);
  delay(500);
}