/**
 * Budget 3D Scanner Control System
 * Written by Toby Chui (Author of the Project)
 * Date: 20-1-2019
 */
#include <Stepper.h>
#include <Wire.h>

const int IR_SENSOR = 0; // Sensor is connected to the analog A0
const int stepsPerRevolution = 200;  // Stepper steps per revolution
const int maxHeight = -600; //Max height of the scanner track
const int repeatMeasurement = 4; //10 measurement averages per pt
String i;

//Tmp vairables
String a;
int endStop;
bool enableSensor = true;

// initialize the stepper library on pins 8 through 11:
Stepper StepR(stepsPerRevolution, 8,9,10,11);
Stepper StepZ (stepsPerRevolution, 4,5, 6, 7);

void setup() {
  Serial.begin(115200);
  Serial.println("[info] Budget 3D Printer Control System");
  // set the speed at 60 rpm:
  StepR.setSpeed(60);
  StepZ.setSpeed(60);
  // initialize the serial port:
  //Set the endstop power pin
  pinMode(13, OUTPUT); 
  pinMode(13, HIGH);
  //Pin 12 as the end stop detection button
  pinMode(12, INPUT);
  Serial.println("[info] Starting I2C connectons...");
  //distance sensor
  Wire.begin();
  Serial.println("[info] Initializing VL53L1X sensor...");
  //Hardware Testing
  Serial.println("[OK] Ready!");
}

void loop() {
  while(Serial.available()) {
    a= Serial.readString();// read the incoming data as string
    if (a== "G28"){
      //Home
      Serial.println("[info] Homing...");
      homing();
    }else if (a == "G93"){
      //Start scanning
      homing();
      delay(1000);
      Serial.println("[info] Scanning started");
      //Don't touch any number in this function. I HAVE TESTED THIS FOR A WEEK!!
      for (int k =0; k > -605; k-=5){
        for (int j =0; j < 200; j++){
          rotate(1);
          scan(k,j);
          delay(100);
        }
        moveUp(-5);
        delay(300);
      }
      Serial.println("[info] Scanning Ended");
      delay(3000);
      homing();
    }else if (a == "G94"){
      //Calibration
      homing();
      moveUp(-200);
      delay(1000);
      float d = 0;
      d = scan_once();
      Serial.println("[Debug] Calibration center: " + (String)d);
      delay(1000);
      homing();
    }else if (a == "G95"){
      Serial.println("[Debug] Moving scanner to top position...");
      homing();
      delay(1000);
      moveUp(-600);
    }else if (a == "G96"){
      Serial.println("[Debug] Rotating platform for a full revolution...");
      rotate(200);
     }else if (a == "G97"){
      Serial.println("[Debug] Checking sensor value...");
      delay(1000);
      float tmp = scan_once();
      Serial.println("[Debug] Calibration center: " + (String)tmp);
    }else{
      Serial.println("[info] Echo: " + a);
    }
  }
  
}
void scan(int h, int r){
  h = h * -1; //Converting the negative domain to positive
  r = r; //Converting counter to rotational steps
  float d = 0;
  float s = 0;
  for (int j = 0; j < repeatMeasurement; j++){
    float distance = scan_once();
    s = distance + s;
  }
  d = s / repeatMeasurement;
  Serial.println((String)h + " " + (String)r + " " + (String)d);
}

float scan_once(){
  float scanValue = 0;
  int scanData = 0;
  scanData = analogRead(IR_SENSOR); //Get sensor value
  scanValue = (6787.0 / (scanData - 3.0)) - 4.0; //Calculate distance in cm
  scanValue = scanValue * 10; //in mm
  return scanValue;
}

void rotate(int steps){
  StepR.step(steps);
}

void moveUp(int steps){
  StepZ.step(steps);
}
void homing(){
  bool reachedBottom = false;
  while(reachedBottom == false){
    endStop = digitalRead(12);
    if (endStop == HIGH) {
      Serial.println("");
      reachedBottom = true;
      Serial.println("[info] Home position reached");
      delay(300);
      StepZ.step(-50);
    }else {
       StepZ.step(1);
       Serial.print(".");
       delay(10);
    }
  }
  return;
}
