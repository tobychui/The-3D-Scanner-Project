/* YourDuino.com Example Software Sketch
   Small Stepper Motor and Driver V1.3 11/30/2013
   http://arduino-direct.com/sunshop/index.php?l=product_detail&p=126
   Shows 4-step sequence, Then 1/2 turn and back different speeds
   terry@yourduino.com */

/*-----( Import needed libraries )-----*/
#include <Stepper.h>

/*-----( Declare Constants, Pin Numbers )-----*/
//---( Number of steps per revolution of INTERNAL motor in 4-step mode )---
#define STEPS_PER_MOTOR_REVOLUTION 32   

//---( Steps per OUTPUT SHAFT of gear reduction )---
#define STEPS_PER_OUTPUT_REVOLUTION 3840 //32 * 64  //2048  
#define echoPin 16 // Echo Pin
#define trigPin 15 // Trigger Pin
/*-----( Declare objects )-----*/
// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to

//The pin connections need to be 4 pins connected
// to Motor Driver In1, In2, In3, In4  and then the pins entered
// here in the sequence 1-3-2-4 for proper sequencing
Stepper small_stepper(STEPS_PER_MOTOR_REVOLUTION, 9, 11, 10, 12);
Stepper platform_stepper(STEPS_PER_MOTOR_REVOLUTION, 3, 5, 4, 6);

/*-----( Declare Variables )-----*/
int  Steps2Take;
int i;
int r;
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(17, OUTPUT);
  digitalWrite(7, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(17, LOW);
  digitalWrite(14, HIGH);

   
//declear base value
i = 0;
r = 0;
 //Steps2Take  =  STEPS_PER_OUTPUT_REVOLUTION  ;  // Rotate CW 1/2 turn
while (i < 3840) {
  while (r < 2048){
    platform_stepper.setSpeed(400);
    platform_stepper.step(128);
    r +=128;
    GetDistance();
    Serial.print(" ");
    Serial.print(r);
    Serial.print(" ");
    Serial.println(i);
  }
  r = 0;
  delay(100);
  small_stepper.setSpeed(200);   
  small_stepper.step(240);
 i += 240;
  //delay(50);
  }
  
  Steps2Take  =  - STEPS_PER_OUTPUT_REVOLUTION;  // Rotate CCW 1/2 turn  
  small_stepper.setSpeed(400);  // 700 a good max speed??
  small_stepper.step(Steps2Take);
  delay(2000);
}/*--(end setup )---*/

int GetDistance(){
  digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in mm) based on the speed of sound.
 distance = duration/58.2 * 10;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 return -1;
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.print(distance);
 return distance;
 }
 
 //Delay 50ms before next reading.
 delay(50);
}


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
 
}
