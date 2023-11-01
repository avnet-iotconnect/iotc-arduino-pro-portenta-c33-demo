# Arduino-PRO-Portenta-C33 Demo
Arduino sketch example demonstrating connection of an [Arduino PRO Portenta C33]([url](https://docs.arduino.cc/hardware/portenta-c33)) to IoTConnect on AWS via Wi-Fi.  The sketch publishes a random simulated temperature reading plus the current UTC time (acquired via online NTP servers) at 1 minute intervals.  Commands sent from IoTConnect to the Portenta C33 are also received and printed to the serial monitor.

# Security & Authentication
Security and authentication are based on a self-signed X.509 certificate inserted into the "arduino_secrets.h" file but are not shown for security purposes.  Note that all SSIDs, passwords, topics, device keys, and certificates are placed in "arduino_secrets.h" file. 

# Getting Started
**Step 1: IoTConnect Registration**
Ensure you have registered and are signed into your IoTConnect account.  Contact our team at [info@iotconnect.io](mailto:info@iotconnect.io) to create an account if needed.

**Step 2: Create a Template for Your Device**
On the left side of the screen, the ribbon shows multiple icons.  Look for the one that looks like an IC with a "Devices" popup as shown below and click on 'Device':

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/a5761e4a-8081-4317-ba14-dfd073e8b2a7)


At the bottom of the 'Device' screen is another ribbon.  Click on 'Templates' 

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/4215b9de-0cb5-4234-86d7-fc7145846972)


Now click on 'Create Template' at the top right of the screen.

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/fa9e81f8-6960-4d25-a5c6-7ca90d05fadd)
