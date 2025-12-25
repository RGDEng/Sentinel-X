/*
 * Project: Sentinel-X Automated Turret
 * Description: Autonomous defense system using Ultrasonic Sensor, Servo, and DC Motor.
 * Features 3 security zones (Safe, Alert, Emergency).
 * Author: RDGEng
 * Date: December 2025
 */

#include <Servo.h>

// --- Component Definitions ---
Servo myTorreta; 

// Outputs (Actuators & Lights)
const int redLed = 2;
const int buzzer = 3;      // Passive Buzzer
const int laser = 12;      // Changed from 8 to avoid conflict
const int PIN_IN3 = 8;     // DC Motor Logic Pin 1
const int PIN_IN4 = 9;     // DC Motor Logic Pin 2
const int pinServo = 13;

// Inputs (Sensors)
const int trigPin = 10;    // HC-SR04 Trigger
const int echoPin = 11;    // HC-SR04 Echo
const int joystickX = A0;  // Joystick X-Axis
const int swButton = 4;    // Joystick Button

// --- Setup Configuration ---
void setup() { 
  Serial.begin(9600); // Initialize Serial Monitor
  
  // Attach Servo
  myTorreta.attach(pinServo);
  
  // Configure Output Pins
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(laser, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  
  // Configure Input Pins
  pinMode(echoPin, INPUT);
  pinMode(swButton, INPUT_PULLUP); // Enable internal pull-up resistor

  // Initial State: Safety OFF
  digitalWrite(laser, LOW);
  digitalWrite(redLed, LOW);
  noTone(buzzer);
}

// --- Main Logic Loop ---
void loop() { 
  long dist = readDistance(); // Get current distance in cm

  // --- ZONE 1: EMERGENCY (< 10cm) ---
  // System takes full control. Panic mode.
  if (dist > 0 && dist < 10) {
    emergencyProtocol();
  
  // --- ZONE 2: ALERT (< 40cm) ---
  // Warning lights ON. Manual fire authorization granted.
  } else if (dist < 40) {
    digitalWrite(redLed, HIGH);
    digitalWrite(laser, HIGH);
    moveTurretManual(); // User keeps control of aiming
    
    // Check Manual Trigger (Active LOW)
    if (digitalRead(swButton) == LOW) {
      fireWeapon();
    }

  // --- ZONE 3: SAFE MODE ---
  // No threats detected. Surveillance mode.
  } else {
    moveTurretManual();
    digitalWrite(redLed, LOW);
    digitalWrite(laser, LOW);
    noTone(buzzer);
    // Ensure motor is stopped
    digitalWrite(PIN_IN3, LOW);
    digitalWrite(PIN_IN4, LOW);
  }
  
  delay(50); // Stability delay
}

// --- Helper Functions ---

// Measure distance using HC-SR04 Ultrasonic Sensor
long readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Calculate distance in cm
  return distance;
}

// Map Joystick input to Servo angle
void moveTurretManual() {
  int val = analogRead(joystickX);
  int angle = map(val, 0, 1023, 0, 180);
  myTorreta.write(angle);
}

// Action: Manual short burst fire
void fireWeapon() {
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW); 
  delay(200); // Burst duration
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
  delay(200); // Cooldown
}

// Action: Automated Panic Mode (Alarm + Continuous Fire)
void emergencyProtocol() {
  digitalWrite(redLed, HIGH);
  digitalWrite(laser, HIGH);
  tone(buzzer, 1000); // 1kHz Alarm tone
  
  // Fire motor
  digitalWrite(PIN_IN3, HIGH);
  digitalWrite(PIN_IN4, LOW);
  
  delay(1000); // Sustain attack for 1 second
  
  // Reset everything
  digitalWrite(redLed, LOW);
  digitalWrite(laser, LOW);
  noTone(buzzer);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, LOW);
}



