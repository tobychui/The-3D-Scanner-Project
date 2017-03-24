# 3D Scanner Ver 2

<img src="https://raw.githubusercontent.com/tobychui/Low-Cost-3D-Sanner-Project/master/Ver2/Image.png">

This version is the 1st successed version of the low cost 3D printer Project with ultrasound Sensor.
For the tutorial to make this scanner, please visit my instructable here:

https://www.instructables.com/id/Ultra-Low-Cost-3D-Scanner/

## Simple Instruction
To use this scanner, you have to build the 3D scanner itself with the 3d models provided here
Next, uplaod the Arduino sketch onto your arduino nano (Arduino UNO will work just fine)
Run the code using Arduino IDE Serial, copy all the returned information into the software "Length to 3D coordinate Scanner Data Convertor"
Convert it from raw information to coordinate data
Copy the exported data and sve them in a text file named "your name here".asc
Open that file in Meshlab for viewing

## How to convert it into stl?
To convert it into stl, you have to import the asc file into Meshlab
From filter, choose Calculate Normal with a sample rate 500 -1000 for the best results.
Next, also from the filter section, select Possion Surface Reconstruction (Or the reconstruction function with the name "Possion" in it if you are using newer version)
Click ok, wait for it and export the stl mesh as usual.
