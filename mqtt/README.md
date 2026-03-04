## Data Transmission and Visualization

The ESP32 transmits the measured tank levels using the MQTT protocol, a lightweight publish/subscribe communication method widely used in IoT systems due to its low bandwidth usage and reliability. In this architecture, the ESP32 acts as the publisher and sends measurement data to an MQTT broker using the topic `camion/donnees`. The transmitted payload is formatted as a JSON message containing the device identifier, timestamp, and the measured liquid levels for both tanks. Node-RED acts as the subscriber, receiving the MQTT messages, parsing the JSON payload, and splitting the data into two separate values corresponding to the used coolant tank and the new coolant tank. These values are then displayed in real time on a Node-RED dashboard using gauge widgets, allowing clear monitoring of the coolant levels in the system.

### Example MQTT Payload

```json
{
  "device_id": "camion_X",
  "timestamp": "2026-03-04T14:30:00Z",
  "liquide_use": 3.12,
  "liquide_neuf": 12.43
}
