/*  3D Scanner controler
 * Recieve steping instruction (rotation:i,height:i)
 * Send Back instruction (rotation:i, height:i, depth:i)
 * 
 * TBD: circula list
 * Tam Yiu Chau 2019
 */
#include <Stepper.h>
#include <VL53L1X.h>
#include <Wire.h>

VL53L1X dS;

Stepper hStep(200,1,2,3,4);
Stepper rStep(200,5,6,7,8);

const int measurePeriod = 50;//(ms)

int cR; //currnet rotation
int cH; //current height
int move_h(int h){
  int delta = h - cH;
  hStep.step(delta);
  cH = h;
  return delta;
}

void move_r(int r){
  int delta = r-cR;
  rStep.step(delta);
  cR = r;
  return delta;
}

int scan(){return 0;}
void setup(){
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);

  dS.setTimeout(500);
  if (!dS.init()){
    Serial.println("Failed to detect and initialize sensor!");
    return -1;
  }
  dS.setDistanceMode(VL53L1X::Short);
  dS.setMeasurementTimingBudget(measurePeriod*1000);

  dS.startContinuous(measurePeriod);
  return 0;
}
char buf[3*4*8];
void loop(){
  Serial.readBytes(buf,2*4*8);
  int rr,rh,rd;
  sscanf("%d%d",buf,&rh,&rr);
  move_h(rh);
  move_r(rr);
  int d = dS.read();//mm
  sprintf("%d%d%d",buf,rh,rr,rd);
  Serial.write(buf,3*4*8);
}
