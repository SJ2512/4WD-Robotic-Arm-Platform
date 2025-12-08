#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ------------------ OLED CONFIG ----------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ------------------ Pins ---------------------
const int IR_PIN = 3;
const int LASER1 = 10;
const int LASER2 = 11;

const int LDR1 = A0;
const int LDR2 = A1;

const int STATUS1 = 9;
const int STATUS2 = 8;

// LEDs
const int BLUE1 = 5;
const int BLUE2 = 4;
const int RED1  = 7;
const int RED2  = 6;


const int BUZZ = 12;

// --- Thresholds
int th1 = 530;   // LDR1 weak beam
int th2 = 80;    // LDR2 strong beam

unsigned long lastAlarmTime = 0;
const unsigned long alarmCooldown = 2000;

void beepShort() {
  digitalWrite(BUZZ, HIGH);
  delay(70);
  digitalWrite(BUZZ, LOW);
  delay(30);
}

void beepLong() {
  digitalWrite(BUZZ, HIGH);
  delay(250);
  digitalWrite(BUZZ, LOW);
  delay(100);
}

void alarmSiren() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(BUZZ, HIGH);
    digitalWrite(RED1, HIGH);
    digitalWrite(RED2, HIGH);
    delay(180);

    digitalWrite(BUZZ, LOW);
    digitalWrite(RED1, LOW);
    digitalWrite(RED2, LOW);
    delay(120);
  }
}

// ------------------ Boot Animation ---------------------
void hackerBoot() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.print(">> Initializing system...");
  display.display(); delay(600); beepShort();

  display.setCursor(0,16);
  display.print(">> Checking sensors...");
  display.display(); delay(600); beepShort();

  display.setCursor(0,26);
  display.print("   LDR1 ........ OK");
  display.display(); delay(400);

  display.setCursor(0,36);
  display.print("   LDR2 ........ OK");
  display.display(); delay(400);

  display.setCursor(0,46);
  display.print("   IR .......... OK");
  display.display(); delay(400); beepShort();

  display.clearDisplay();
  display.setCursor(0,0);
  display.print(">> Booting Kernel 1.9");
  display.display(); delay(500);

  display.setCursor(0,16);
  display.print(">> Establishing Laser");
  display.display(); delay(600);

  display.setCursor(0,26);
  display.print(">> Loading Modules...");
  display.display(); delay(500);

  // Fake progress bar
  for(int i=0; i<120; i+=10){
    display.fillRect(0, 50, i, 10, SSD1306_WHITE);
    display.display();
    delay(100);
  }

  beepLong();
  delay(300);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print("READY");
  display.display();
  delay(800);
}
void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED FAILED");
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  pinMode(IR_PIN, INPUT);
  pinMode(LASER1, OUTPUT);
  pinMode(LASER2, OUTPUT);

  pinMode(STATUS1, OUTPUT);
  pinMode(STATUS2, OUTPUT);

  pinMode(BLUE1, OUTPUT);
  pinMode(BLUE2, OUTPUT);
  pinMode(RED1, OUTPUT);
  pinMode(RED2, OUTPUT);

  pinMode(BUZZ, OUTPUT);
  digitalWrite(BUZZ, LOW);

  digitalWrite(LASER1, HIGH);
  digitalWrite(LASER2, HIGH);
  digitalWrite(BLUE1, HIGH);
  digitalWrite(BLUE2, HIGH);

  hackerBoot();

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("SYSTEM ARMED");
  display.setCursor(0, 16);
  display.print("Monitoring...");
  display.display();

  Serial.println("System Running w/ OLED");
}


void triggerAlarm(const char* msg) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("ALARM!");

  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print(msg);
  display.display();

  digitalWrite(BLUE1, LOW);
  digitalWrite(BLUE2, LOW);

  alarmSiren();   // 🔥 SOUND + RED FLASH

  lastAlarmTime = millis();
}

void loop() {

  if (millis() - lastAlarmTime < alarmCooldown) return;

  int irState = digitalRead(IR_PIN);
  int v1 = analogRead(LDR1);
  int v2 = analogRead(LDR2);

  Serial.print("LDR1=");
  Serial.print(v1);
  Serial.print(" | LDR2=");
  Serial.println(v2);

  if (irState == HIGH) {
    triggerAlarm("Artifact Taken");
    return;
  }

  if (v1 < th1) {  
    digitalWrite(STATUS1, HIGH);
    triggerAlarm("Beam 1 Active");
    return;
} else {
    digitalWrite(STATUS1, LOW);
}


  if (v2 > th2) {
    digitalWrite(STATUS2, HIGH);
    triggerAlarm("Beam 2 Break");
    return;
  } 
  else digitalWrite(STATUS2, LOW);

  digitalWrite(BLUE1, HIGH);
  digitalWrite(BLUE2, HIGH);
  digitalWrite(RED1, LOW);
  digitalWrite(RED2, LOW);

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0, 0);
  display.print("SYSTEM ARMED");

  display.setCursor(0, 16);
  display.print("Beam1: ");
  display.print(v1);

  display.setCursor(0, 28);
  display.print("Beam2: ");
  display.print(v2);

  display.setCursor(0, 48);
  display.print("Monitoring...");
  display.display();
}
