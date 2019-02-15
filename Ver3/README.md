# Budget 3D Scanner Version 3

### Introduction
This is another 3D Scanner built with Arduino and Distance Sensor. Different from the other versions before, this version has a modular design and you can mount different type of sensor on the moving platform. 

<img src="https://raw.githubusercontent.com/tobychui/The-3D-Scanner-Project/master/Ver3/rendering/rendering/render.306.png">

### How it works
There are two stepper motors in this device. One used for the platform rotation and one for movint the scanning platform up and down. The rotating platform will represent (and scan) the x / y location of the object while the another stepper will manage the sensor in z direction.

<img src="https://raw.githubusercontent.com/tobychui/The-3D-Scanner-Project/master/Ver3/Images%20and%20Icons%20(Processed)/side%203.png">

### Instllation
1. 3D Printed all parts from the 3D Model folder. If the parts name is followed by a version number (e.g. parts ver2.stl), use the latest version instead.
2. Prepare the screws needed (All of them are M3 screws either M3 * 5, M3 * 10 or M3 * 20),screw in every screw holes on the 3D model as all of them are necessary.
3. Build the pully guider and glue the pully system in place to the body of the scanner with super glue
4. Install the end stop at the bottom of the devices where next to the bottom pully.
5. Flash in the Arduino code. Use ver 2.2 if you are using VL53L1X ToF Sensor or the infra edition if you are using SHARP IR Sensors
6. Insert all the stepper motor pins to the stepper driver (L298 * 2), and connect the stepper driver to the Arduino pins (4,5,6,7 and 8,9,10,11). Connect the ToF Sensor to SDA and SCL pins or the IR sensor to the A0 pins
7. Plug in the power and do a test run. If everything is doing right, you can now install the stepper motors into the scanner body.
8. Use some imagination of anything didn't fits right :)

More details and scan results can be fnd in "Budget 3D Scanner Project.pdf" and operation video "quickdemo.mp4"

### Disclaimer
This project is developed by Toby (Me) and Andy, in which Andy was the guy who wrote the pos-processing scripts.
See his repo here:

<a href="https://github.com/tamyiuchau/Budget3dPrinter">https://github.com/tamyiuchau/Budget3dPrinter</a>

