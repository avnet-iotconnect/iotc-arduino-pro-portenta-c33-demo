# Arduino-PRO-Portenta-C33 Demo
Arduino sketch example demonstrating connection of an [Arduino PRO Portenta C33](https://docs.arduino.cc/hardware/portenta-c33) to IoTConnect on AWS via Wi-Fi.  The sketch publishes a random simulated temperature measurement plus the current UTC time (acquired via online NTP servers) at 1 minute intervals.  Commands sent from IoTConnect to the Portenta C33 are also received and printed to the serial monitor illustrating full bidirectional MQTT communication.

# Portenta C33 Features
The Portenta C33 is a powerful System-on-Module based on the R7FA6M5BH2CBG microcontroller, which utilizes the high-performance Arm® Cortex®-M33 core. The Portenta C33 shares the same form factor as the Portenta H7, and it is backward compatible with it. The Portenta C33 is fully compatible with all Portenta family shields and carriers through its MKR-styled and High-Density connectors.

The board also supports MicroPython and other high-level programming languages, allowing developers to write code in a familiar language and accelerate development. With its onboard Wi-Fi® and Bluetooth® connectivity, the Portenta C33 is the ideal solution for Internet of Things (IoT) gateways, remote control systems, fleet management, and process tracking. These features allow the Portenta C33 to connect easily to other devices and sensors, enabling seamless data transfer and real-time control in various applications.  Using the onboard secure element, Avnet is able to provide security management services for deployments at scale.

# Security & Authentication
Security and authentication are based on an X.509 certificate inserted into the "arduino_secrets.h" file.  Note that all sensitive information (SSIDs, passwords, topics, device keys, and certificates) are placed in "arduino_secrets.h" where each is preceded by "SECRET_xxxx" which is an Arduino method of allowing files to be shared while protecting sensitive information.  Refer to [this document](https://docs.arduino.cc/arduino-cloud/tutorials/store-your-sensitive-data-safely-when-sharing) for details.   

# Arduino Libraries
With the vast number of Arduino libraries available, locating a suitable library may sometimes slow development.  This demo utilizes the Arduino libraries listed below which will need to be installed prior to compiling the sketch should you choose to use them.  
- [MQTT Client v0.1.7 by Arduino](https://github.com/arduino-libraries/ArduinoMqttClient)
- [ESP_SSL Client v2.1.7 by Mobizt](https://github.com/mobizt/ESP_SSLClient)
- [ArduinoJson v6.21.3 by Benoit Blanchon](https://arduinojson.org/)
- [Arduino-timer v3.0.1 by Michael Contreras](https://github.com/contrem/arduino-timer/tree/master): 
- [Arduino Connection Handler v0.7.7 by Ubi de Feo, Christian Maglie...](https://github.com/arduino-libraries/Arduino_ConnectionHandler)
- [NTPClient v3.2.1 by Fabrice Weinberg](https://github.com/arduino-libraries/NTPClient)

Avnet also provides libraries and SDKs to accelerate your development effort.  Please refer to the [IoTConnect documentation](https://docs.iotconnect.io/iotconnect/) for more information.

# Prerequisites
1. An [Arduino Portenta C33 SOM](https://www.newark.com/arduino/abx00074/arduino-portenta-c33-rohs-compliant/dp/77AK2285)
2. A suitable Wi-Fi/BLE antenna connected to the C33.  This should be furnished with the C33.  Refer to the Arduino instructions for attachment.
3. A suitable USB cable to connect your development PC to the C33.  The C33 has a USB-C connector for both data and power.
4. A working installation of the Arduino IDE (v2.2.1 or later)
5. The previously listed Arduino libraries installed.
6. Download of all files in this repository
7. A working IoTConnect account.  Request a free trial account if you don't already have one.

# Request a Free IoTConnect Trial Account
Avnet's IoTConnect platform is available on either AWS or Microsoft Azure although this demo runs exclusively on the AWS version.
The IoTConnect team will release a self-sign-up portal for new customers to request a free trial account.  The scheduled release is Jan 2024.  Until then, you can send an email to [info@iotconnect.io](mailto:info@iotconnect.io) or visit the [Contact us](https://www.avnet.com/wps/portal/us/solutions/iot/contact-us/) page on Avnet.com.

# Getting Started
Once your prerequisites are satisfied you will need to create a virtual device on IoTConnect.  Each virtual device is based on a 'template' which is a self-contained file that defines the message protocol, attributes, commands, and authentication method.  A high level outline of the required steps is as follows:
1. In IoTConnect create a device template.  
2. In IoTConnect create a virtual device based on the template .
3. IoTConnect will create a device certificate & key which, when downloaded to your C33, uniquely identify your device to IoTConnect and enable encrypted communications.
4. Complete the 'arduino_secrets.h' file with information from your virtual device (along with your Wi-Fi network parameters).
5. Compile and download the demo code to the C33

# Creating a Device Template
1. From the IoTConnect main screen, click on the 'Devices' icon which looks like an IC, then click on 'Device'

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/256b54ad-6d40-4cab-a7b0-8d568324e7af)

2. At the bottom of your screen select the **Templates tab** from leftmost side of the ribbon

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/3ac659ae-f963-40ab-a941-f4b52845f18b)

3. Search the existing templates for one called "PortentaC33Demo_template.JSON".  If it is listed, you can skip this section and proceed to **Create a Virtual Device**.  If not, import the template from the ([PortentaC33Demo_template.JSON](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/blob/main/PortentaC33Demo_template.JSON)) file included in this repo.  To import it, use the 'Import' button at the upper right of the screen

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/f52607bf-6a29-41e6-b69d-cfaf54086eb5)

4. A popup window will appear and allow you to browse for the template on your PC.

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/107dcb84-161f-409e-8e76-fb2a9ff64b50)

5.  Click 'Save'.  The template should now be visible in the list of templates.  If you received a warning message about the template already exists you can procede to the next section.

# Create a Virtual Device

1.  On the ribbon at the bottom of the screen click on 'Devices'
2.  At the upper right of the screen click on 'Create Device'
3.  The **Create Device** form opens.  Fill it out and click the **Save** button when finished.
    - Ensure the **Unique Id** field does not contain spaces or special characters
    - You may have only a single option for **Entity** which will likely be different from the one shown
    - Select the **Template** that matches the name shown below or the one you imported       

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/727e7dd2-728b-4ac9-9541-ac42d118e7af)

4.  Your virtual device should now appear in the list of Devices and clicking on the leftmost field should take you to the device's **Info Screen**

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/de153739-4913-4a3f-8d5f-d9ae80d1b183)

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/d3e56bee-14ae-4b70-8ac3-6ca8f7a0f561)

5.  Click on 'Connection Info' towards the upper right of the screen.  A window will open which contains vital information for your device to connect to IoTConnect

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/cf91de64-23c6-4943-b477-766394bea9fc)


6.  Copy the following information from this IoTConnect **Connection Info** window into your **arduino_secrets.h** file:
     - Copy the **#host** field and paste into your local **arduino_secrets.h** file in the **SECRET_BROKER** field.
     - Copy the **#clientID** field and paste into your local **arduino_secrets.h** file in the **SECRET_CLIENT_ID** field
     - Copy the **#reporting** field and paste into your local **arduino_secrets.h** file in the **SECRET_TOPIC** field
     - Copy the **#acknowledgement** field and paste into your local **arduino_secrets.h** file in the **SECRET_ACK_TOPIC** field
     - Copy the **#cloudToDevice** field and paste into your local **arduino_secrets.h** file in the **SECRET_CMD_TOPIC** field
  
 Your **arduino_secrets.h** file should have a section resembling the following:

 ![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/ede769cf-7d82-474d-b165-e3bd374ecbb5)

 7.  Click on the download certificates icon in the upper right.  This will download a zip file containing the device certificate and private key to your PC in the default download directory.  You may close the IoTConnect **Connection Info** window at this point. The contents of the zip file are as shown:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/53564fea-b8d2-4b20-967c-cf04b36e3024)


Unzip the file into a local directory.  You will need to open each file with Notepad or similar text editor program.









 

