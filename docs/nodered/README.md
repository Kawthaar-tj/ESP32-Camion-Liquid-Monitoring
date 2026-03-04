### Node-RED Dashboard

![Node-RED Dashboard](docs/nodered/dashboard.png)

The Node-RED dashboard provides a real-time visualization of the coolant levels in both tanks. 
Two gauge widgets are used to display the measured volumes: one for the new coolant tank and one 
for the used coolant tank. The values are updated automatically each time a new MQTT message is 
received from the ESP32, allowing continuous monitoring of the system.
