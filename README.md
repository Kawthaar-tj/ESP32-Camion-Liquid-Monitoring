#Liquid Tank Monitoring System – Embedded IoT Project
#Project Overview

This project is an embedded IoT system designed to monitor two liquid tanks (fresh liquid and used liquid) inside a maintenance truck.

The system measures liquid level using resistive sensors, converts the measurements into calibrated volume values, displays real-time information locally on an LCD screen, and transmits structured data to a remote server via MQTT over WiFi.

The solution was designed to operate reliably in a 12V automotive electrical environment.

#System Features

Monitoring of two liquid tanks
Resistive level sensing (33Ω – 190Ω range)
Voltage divider signal conditioning
12-bit ADC acquisition (ESP32)
Calibration-based percentage estimation
Volume calculation in liters
Real-time display on 16x2 I2C LCD
WiFi communication
MQTT JSON data transmission
Compatible with Node-RED / cloud dashboard

#System Architecture

Resistive Sensor → Voltage Divider → ESP32 ADC → Data Processing → LCD Display
ESP32 → WiFi → MQTT Broker → Server / Dashboard

The ESP32 handles acquisition, signal processing, display management, and cloud communication.

#Hardware Components

ESP32 (SparkFun ESP32 Thing)
2x Analog resistive level sensors (33–190Ω)
150Ω precision resistors (voltage divider)
16x2 I2C LCD display
LM2596 DC-DC buck converter (12V → 5V)
12V truck battery supply

#Measurement Principle

#Resistive Level Sensor

Each tank uses a resistive float-type level sensor.
The sensor resistance varies depending on the liquid level:

Low level → approximately 33Ω
High level → approximately 190Ω

Since the sensor outputs resistance and not voltage, a voltage divider circuit is required.

#Voltage Divider Design

The sensor is combined with a 150Ω fixed resistor to convert resistance variation into a measurable voltage.

Vout = Vcc × (Rsensor / (Rfixed + Rsensor))

With:

Vcc = 3.3V
Rfixed = 150Ω
Rsensor = 33–190Ω

Maximum output voltage ≈ 1.84V

This ensures:

Safe operation within ESP32 ADC limits
No need for amplification stage
Stable analog acquisition

#Signal Processing

12-bit ADC reading (0–4095)
Voltage conversion (0–3.3V reference)
Calibration curve using measured reference points
Linear interpolation for percentage estimation
Volume calculation based on tank geometry

#Electrical Architecture

Input voltage: 12V (truck battery)
Buck converter (LM2596) reduces voltage to 5V
ESP32 internal regulator provides 3.3V
Analog inputs connected to GPIO 34 and GPIO 35
Common ground reference
Designed for automotive supply conditions

#MQTT Data Format

The system transmits structured JSON data to the MQTT broker:

{
"device_id": "camion_X",
"timestamp": "2026-02-19T10:30:00Z",
"liquide_use": 7.2,
"liquide_neuf": 12.4
}

#Engineering Considerations

Signal adaptation for resistive sensors
ADC voltage protection
Calibration for sensor non-linearity
Separation of power and analog measurement stages
Automotive power compatibility
Reliable WiFi communication in mobile environment

#Future Improvements

Custom 2-layer PCB design
Automotive protection stage (fuse + TVS diode)
OTA firmware updates
Data logging on SD card
Power consumption optimization
Sensor fault detection algorithm
Enclosure design for field deploymen
