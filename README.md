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
- [ArduinoJson v6.21.3 by Benoit Blanchon](https://arduinojson.org/)
- [Arduino-timer v3.0.1 by Michael Contreras](https://github.com/contrem/arduino-timer/tree/master): 
- [Arduino Connection Handler v0.7.7 by Ubi de Feo, Christian Maglie...](https://github.com/arduino-libraries/Arduino_ConnectionHandler)
- [NTPClient v3.2.1 by Fabrice Weinberg](https://github.com/arduino-libraries/NTPClient)
- [Time by Michael Margolis v1.6.1 ](https://playground.arduino.cc/Code/Time/)

Avnet also provides libraries and SDKs to accelerate your IoTConnect development effort.  Please refer to the [IoTConnect documentation](https://docs.iotconnect.io/iotconnect/) for more information.

# Prerequisites
1. An [Arduino Portenta C33 SOM](https://www.newark.com/arduino/abx00074/arduino-portenta-c33-rohs-compliant/dp/77AK2285)
2. A suitable Wi-Fi/BLE antenna connected to the C33.  This should be furnished with the C33.  Refer to the [Arduino C33 User Manual](https://docs.arduino.cc/tutorials/portenta-c33/user-manual) for details.

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/d4de69a6-3fbb-426f-a634-0b8b03e0d08c)


3. A suitable USB cable to connect your development PC to the C33.  The C33 has a USB-C connector for both data and power.
4. A working installation of the Arduino IDE (v2.2.1 or later).  You may use the cloud based IDE which was not used to create this demo.  Your setup procedures may differ!
5. A working IoTConnect account **on AWS**.  Request a free trial account if you don't already have one.

# IoTConnect Account Setup
This guide requires an IoTConnect account on AWS.

>**NOTE:**  
> If you have already created an IoTConnect account on AWS, or were provided an account as part of a training or workshop, skip this section.

If you need to create an account, a free 2-month subscription is available.
Please follow the 
[Creating a New IoTConnect Account](https://github.com/avnet-iotconnect/avnet-iotconnect.github.io/blob/main/documentation/iotconnect/subscription/subscription.md)
guide and ensure to select the [AWS version](https://subscription.iotconnect.io/subscribe?cloud=aws) during registration:

![IoTConnect on AWS](https://github.com/avnet-iotconnect/avnet-iotconnect.github.io/blob/main/documentation/iotconnect/subscription/media/iotc-aws.png)

# Getting Started
1. Once your prerequisites are obtained, if you are using a local IDE you will need to setup the project by installing the list of Arduino libraries mentioned above.  Use the IDE to install them by clicking on the **'Library Manager Icon'** on the left side of the IDE as shown here:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/ac5f47dd-4a27-40e6-8d7f-78d9faea0d26)

Search for the libraries by name and install them.  This example was created using the versions shown which will likely have been updated.  The demo may or may not work with newer libraries so install at your own risk.

2. Next you will need to create a working folder for the Sketch.  On the IDE, navigate to **File->Preferences..**.  On the popup window, the first line should show your Sketchbook location.  Use File Explorer to navigate to this location and make a new folder there called **"C33SecureProv"**  
3. Download the files from this repository into the **"C33SecureProv"** folder you just created.  This README.md file is not required.  
4. You should now see the **C33SecureProv.ino** file in your Sketchbook folder.  You can open the Sketch for editing.

# Creating a Device Template
Creating a device template is the first step in setting up IoTConnect to work with your device.  A device template is a self-contained file that defines the message protocol, attributes (data types), commands, and authentication method.  For this demo, a template has been created for you.  If you were to start from scratch, the template creation screens simplify the process. With that, a high level outline of the required steps for device onboarding is as follows:

    - In IoTConnect create a device template (completed)
    - In IoTConnect create a virtual device based on the template
    - IoTConnect will create a device certificate & key which, when downloaded to your C33, uniquely identifies your device to IoTConnect and enables encrypted communications
    - Complete the 'arduino_secrets.h' file with information from your virtual device (along with your Wi-Fi network parameters).
    - Compile and download the demo code to the C33
    - Observe the data exchanged on IoTConnect and your local Arduino IDE
    - Send commands from IoTConnect to your device
    
    

1. From the IoTConnect main screen, click on the 'Devices' icon which looks like an IC, then click on 'Device'

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/256b54ad-6d40-4cab-a7b0-8d568324e7af)

2. At the bottom of your screen select the **Templates tab** from leftmost side of the ribbon

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/3ac659ae-f963-40ab-a941-f4b52845f18b)

3. Search the existing templates for one called "PortentaC33Demo_template.JSON".  Remember or write down this name, you will use it in the **Create a Virtual Device** procedure below.  If not, double check that you are using an AWS based IoTConnect tenant.

# Create a Virtual Device

1.  On the ribbon at the bottom of the screen click on 'Devices'
2.  At the upper right of the screen click on 'Create Device'
3.  The **Create Device** form opens.  Fill it out and click the **Save** button when finished.
    - Ensure the **Unique Id** field does not contain spaces or special characters
    - You may have only a single option for **Entity** which will likely be different from the one shown
    - Select the **Template** that matches the name shown below      

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/727e7dd2-728b-4ac9-9541-ac42d118e7af)

4.  Your virtual device should now appear in the list of Devices and clicking on its **Unique ID** field should take you to the device's **Info Screen** as shown here:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/d3e56bee-14ae-4b70-8ac3-6ca8f7a0f561)


5.  Click on the **'Connection Info'** text below the red **'Disconnected** icon and proceed to the next section

 ![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/046ac427-7543-4c3b-b27d-e5d68f664d34)



# Copy Device Information
So far we have obtained a device template and with it, we created a virtual device on IoTConnect.  The virtual device contains information that your actual device will use to communicate with IoTConnect.  Let's get that information and place it into your local Portenta C33 file called '**arduino_secrets.h**

1.  When you clicked on 'Connection Info' in the previous step, a window opened containing vital information for your device to connect to IoTConnect.  Notice that field **names** are on the left preceeded by a '#' and the **'values** are on the right.

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/cf91de64-23c6-4943-b477-766394bea9fc)


2.  Copy the following information from this IoTConnect **Connection Info** window into your **arduino_secrets.h** file.  Copy the text by clicking on the **copy** icon:
     - Copy the **#host** value and paste into your local **arduino_secrets.h** file in the **SECRET_BROKER** value
     - Copy the **#clientID** value and paste into your local **arduino_secrets.h** file in the **SECRET_CLIENT_ID** value
     - Copy the **#reporting** value and paste into your local **arduino_secrets.h** file in the **SECRET_TOPIC** value
     - Copy the **#acknowledgement** value and paste into your local **arduino_secrets.h** file in the **SECRET_ACK_TOPIC** value
     - Copy the **#cloudToDevice** value and paste into your local **arduino_secrets.h** file in the **SECRET_CMD_TOPIC** value
  
 A section of your **arduino_secrets.h** file should resemble the the one shown here:

 ![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/ede769cf-7d82-474d-b165-e3bd374ecbb5)

 3.  Go back to the **Connection Info** window and click on the download certificates icon in the upper right.  This will download a zip file containing the device certificate and private key to your PC in the default download directory.  You may close the IoTConnect **Connection Info** window at this point.  The certificate & key you just downloaded allow IoTConnect to authenticate your C33.  The contents of the zip file are as shown.  Yours may differ slightly:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/53564fea-b8d2-4b20-967c-cf04b36e3024)


Unzip the files into a local directory. We will go back to them shortly. 

 4.  For added security, your C33 should authenticate IoTConnect to ensure it is not communicating with an imposter.  To enable that, you will need an AWS root CA certificate (as this version of IoTConnect is on AWS).  You can find that root CA [HERE](https://www.amazontrust.com/repository/SFSRootCAG2.pem) which opens another window (or tab) in your browser with text like this:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/a2787a33-a869-467d-81ba-a785e87dcfcc)

Select all of the text (Windows users can use **Ctrl A**) and copy it (**Ctrl C**)


![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/49505712-c465-4f52-b3dc-2079d40b62f8)


Go to your local **arduino_secrets.h** file and find the line containing **"SECRET_ROOTCERT[]"**.  Delete the text on that line that says "Insert AWS RooT CA here" and paste **(Ctrl V)** the copied text in its place.  It should look like this:


![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/85cb5083-f9eb-4f4b-9ec6-0b421c58af98)


 5.  Okay, we are almost there.  Going back to the 2 files you unzipped in step 3:
- cert_MyPortentaDemo.crt  (device certificate)
- pk_MyPortentaDemo.pem    (private key)

You next step is to open each of these files in a word editor (I use Notepad.exe).  You will copy the entire contents and paste it into your local **arduino_secrets.h** file just like you did with the AWS Root CA.

Let's start with **cert_MyPortentaDemo.crt**.  Open **Notepad** then drag the **cert_MyPortentaDemo.crt** icon into the Notepad window.  The text should almost exactly like the AWS Root CA text. 
- In Notepad, select all of the text using **Ctrl A** then copy it using **Ctrl C**
- Navigate to your local **arduino_secrets.h** file and fine the line containing **"PROGMEM SECRET_DEVCERT[]"**
- On that line, delete the text that reads **"Insert Device Cert here"** and paste the copied text using **Ctrl V**


You will do the same with **pk_MyPortentaDemo.pem**.  Open **Notepad** then drag the **pk_MyPortentaDemo.pem** icon into the Notepad window.
- In Notepad, select all of the text using **Ctrl A** then copy it using **Ctrl C**
- Navigate to your local **arduino_secrets.h** file where it reads **"PROGMEM SECRET_PRIKEY[]"**
- On that line, delete the text **"Insert Key here"** and paste the copied text using **Ctrl V**

# Enter Your Wi-Fi Details
In your local **arduino_secrets.h** file, enter the SSID of your Wi-Fi network in between the quotes for **SECRET_SSID** (line 2).

Next, enter your Wi-Fi password in between the quotes for **SECRET_PASS**

**SAVE YOUR arduino_secrets FILE !!!**

# Connect your C33 board to your PC using the USB cable
See the Portenta [C33 User Manual](https://docs.arduino.cc/tutorials/portenta-c33/user-manual#powering-the-board) for more information on connecting and powering the C33. 

# Compile and Download the Code
If the IDE connects to your board, the 'Upload' button will compile and download the sketch to your C33

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/46fe380f-7c11-41e9-a9c8-797df285f8af)


# View the Telemetry
Once the downloader has finished, open the **'Serial Monitor'** to see the messages to/from the C33 viewable at the bottom of the Arduino IDE

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/31172848-ff68-4237-9df8-b096efff427d)



View the data on IoTConnect by navigating to Devices->Device->Live Data in your browser


![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/0b5d1745-005b-4347-b8e0-bac02ccaf9e1)


# Send a Command
Click on **'Command'** on the left.  The screen below will be shown:

![image](https://github.com/avnet-iotconnect/iotc-arduino-pro-portenta-c33-demo/assets/49933990/1435c583-9d0a-4b06-a1ff-2fdf1eab48ff)

On the **'Command'** drop down select **'Send Line'** which simply sends whatever you type in the **'Parameter Value'** field.
Click on **'Execute Command'** button and your text should show up in the **'Serial Monitor'**.

# Go Further
There are many more capabilities and tools available to you from Avnet.  Contact your Avnet resource for more information.










 

