## Project Overview

This project implements a dual liquid level monitoring system using an ESP32 microcontroller 
and resistive float-based level sensors (reed switch technology).

Each sensor provides a variable resistance (≈ 33–190 Ω) depending on the liquid height. 
The resistance is converted into a measurable voltage using a voltage divider and read 
through the ESP32 ADC.

To ensure measurement accuracy in real-world embedded conditions:
- An experimental calibration table was created,
- Linear interpolation is used for continuous level estimation,
- A software compensation offset is applied to account for the non-measurable mechanical zone.

The system features:
- Dual tank monitoring
- LCD 1602 I2C real-time display
- 12V to 5V regulated power architecture (LM2596)
- MQTT publishing for remote visualization via Node-RED
- Designed for integration inside a truck workshop environment

The architecture is modular and can be extended to additional tanks or cloud-based monitoring.
## Hardware Wiring Diagram

![Wiring Diagram](docs/wiring/wiring_diagram.png)
