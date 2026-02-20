**This project is an embedded IoT system designed to monitor two liquid tanks (used liquid and fresh liquid) inside a maintenance truck**

#The system: 
- Reads analog level sensors
- Converts voltage to percentage using calibration curve
- Calculates tank volume in liters
- Displays values on an I2C LCD
- Sends data to an MQTT broker via WiFi

#System Architecture
-ESP32 → WiFi → MQTT Broker → Server / Node-RED Dashboard

#Hardware Components
-ESP32
-2x Analog level sensors
-16x2 I2C LCD
-12V truck battery supply
-DC-DC converter (12V → 5V)

#Measurement Processing
-ADC reading (12-bit resolution)
-Voltage conversion (0–3.3V)
-Linear interpolation using calibration points
-Volume calculation in liters

#MQTT JSON Payload
{
  "device_id": "camion_X",
  "timestamp": "2026-02-19T10:30:00Z",
  "liquide_use": 7.2,
  "liquide_neuf": 12.4
}

#Electrical Architecture
-Input voltage: 12V (truck battery)
-Buck converter to 5V
-Analog inputs on GPIO 34 and 35
-3.3V regulation for ESP32
-Analog inputs on GPIO 34 and 35

#Future Improvements

