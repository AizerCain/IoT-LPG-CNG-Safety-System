# 📄 Component Datasheets

This folder contains references and technical specifications for the hardware components used in the Gas Leakage Detector project.

## 1. Gas Sensor (MQ-6 / MQ-2)
* **Component:** Winsen MQ-6 (LPG/Isobutane/Propane)
* **Description:** The MQ-6 is a semiconductor gas sensor that detects the presence of LPG, isobutane, and propane concentrations from 200 to 10000ppm.
* **Datasheet Link:** [Download MQ-6 Datasheet (Sparkfun)](https://www.sparkfun.com/datasheets/Sensors/Biometric/MQ-6.pdf)
* **Key Specs:**
    * Heater Voltage: 5.0V ±0.1V
    * Loop Voltage: ≤ 24V DC
    * Load Resistance: Adjustable (20kΩ recommended)
    
  ## 2. GSM Module (SIM900A / SIM800L)
* **Component:** SIMCom SIM900A
* **Description:** A dual-band GSM/GPRS module that operates on frequencies 900MHz and 1800MHz. It allows the Arduino to send SMS and make calls.
* **Datasheet Link:** [SIM900A Hardware Design Manual](https://www.simcom.com/) _(Note: Official links vary by region; refer to your specific module vendor's documentation)_
* **Key Specs:**
    * Supply Voltage: 3.4V - 4.4V (High current spikes up to 2A)
    * Logic Level: 2.8V (May require level shifting for 5V Arduinos, though simple resistor dividers often work)
  
  ## 3. Microcontroller (Arduino Uno R3)
* **Component:** Arduino Uno R3 (ATmega328P)
* **Datasheet Link:** [Arduino Uno R3 Technical Specs](https://docs.arduino.cc/hardware/uno-rev3)
* **Key Specs:**
    * Operating Voltage: 5V
    * Input Voltage (recommended): 7-12V