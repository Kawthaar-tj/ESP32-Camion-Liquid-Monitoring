## Data Transmission – MQTT

The ESP32 transmits the measured tank levels using the MQTT protocol.

MQTT is a lightweight publish/subscribe messaging protocol widely used in IoT
systems due to its low bandwidth usage and simplicity.

In this system:

- The ESP32 acts as the **publisher**
- The MQTT broker receives the data
- Node-RED acts as the **subscriber** to process and visualize the data

### MQTT Topic

camion/donnees
