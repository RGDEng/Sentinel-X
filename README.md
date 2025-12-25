# Sentinel-X: Automated Arduino Defense Turret 🛡️🤖

**Sentinel-X** is an autonomous security system powered by Arduino. It uses an ultrasonic sensor to detect proximity threats and features a 3-zone logic system controlling a servo-mounted turret, a laser targeting system, and a motorized firing mechanism.

## 🌟 Features
* **Manual Control:** Joystick-operated servo aiming (0-180 degrees).
* **Smart Detection:** HC-SR04 ultrasonic sensor for real-time distance tracking.
* **3-Zone Logic System:**
    * 🟢 **Safe Zone (>40cm):** Surveillance mode. Manual control active.
    * 🟡 **Alert Zone (10-40cm):** Laser & LED indicators ON. Manual trigger authorized.
    * 🔴 **Emergency Zone (<10cm):** Full system override. Auto-alarm and auto-fire engaged.
* **Feedback:** Visual (Red LED/Laser) and Audio (Piezo Buzzer) warnings.

## 🛠️ Hardware List
* Arduino UNO
* Servo Motor (SG90)
* Ultrasonic Sensor (HC-SR04)
* DC Motor (with L298N Driver)
* Joystick Module
* Laser Diode & Passive Buzzer
* LEDs & Resistors

## 🚀 How to Run
1.  Connect the components according to the pin definitions in the code.
2.  Upload `SentinelX.ino` to your Arduino board.
3.  Power the L298N driver with external batteries (do not rely on USB power for motors).


