//#define DEBUG_ULTRASONIC

#include <Servo.h>
Servo leftMotor;
Servo rightMotor;
Servo intakePyramid;
Servo liftPyramid;

#define LEFT_MOTOR PA9
#define RIGHT_MOTOR PC7
#define INTAKE_PYRAMID PB6
#define LIFT_PYRAMID PA7

#define FR_ULTRASONIC_IN PC1
#define FR_ULTRASONIC_OUT PC0
#define RI_ULTRASONIC_IN PA4
#define RI_ULTRASONIC_OUT PB0

#define WALL_LOWER_THRESHOLD 5
#define WALL_UPPER_THRESHOLD 10

#define TURN_THRESHOLD 10

#define FORWARD_SPEED 1700
#define REVERSE_SPEED 1700

unsigned long FR_ultrasonic_dist;
unsigned long RI_ultrasonic_dist;
unsigned long FRecho;
unsigned long RIecho;
int cubeRetrieved = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(FR_ULTRASONIC_IN, OUTPUT);
  pinMode(RI_ULTRASONIC_IN, OUTPUT);
  pinMode(FR_ULTRASONIC_OUT, INPUT);
  pinMode(RI_ULTRASONIC_OUT, INPUT);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  pinMode(INTAKE_PYRAMID, OUTPUT);
  pinMode(LIFT_PYRAMID, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);
  intakePyramid.attach(INTAKE_PYRAMID);
  liftPyramid.attach(LIFT_PYRAMID);

}

void loop() {
  if (!cubeRetrieved) {
    // put your main code here, to run repeatedly:
    checkCube();
    
    pingFR();
    pingRI();
  
    if(RI_ultrasonic_dist < WALL_UPPER_THRESHOLD && RI_ultrasonic_dist > WALL_LOWER_THRESHOLD){
      goForward();
    }
    else if(RI_ultrasonic_dist > WALL_UPPER_THRESHOLD){
      moveIn();
    }
    else{
      moveOut();
    }
  
    if(FR_ultrasonic_dist < TURN_THRESHOLD){
      TurnLeftOnAxis(90);
    }
  }
  else if (cubeRetrieved) {
    
  }

#ifdef DEBUG_ULTRASONIC
  Serial.print("RI: ");
  Serial.print(RI_ultrasonic_dist);
  Serial.print("  FR: ");
  Serial.println(FR_ultrasonic_dist);
#endif
}

void pingFR(){

  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(FR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(FR_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  FRecho = pulseIn(FR_ULTRASONIC_OUT, HIGH, 10000);
  if(FRecho) FR_ultrasonic_dist = FRecho/58;
}

void pingRI(){

  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(RI_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(RI_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  RIecho = pulseIn(RI_ULTRASONIC_OUT, HIGH, 10000);
  if(RIecho) RI_ultrasonic_dist = RIecho/58;
}

void TurnLeftOnAxis(int deg){
  leftMotor.writeMicroseconds(1250);
  rightMotor.writeMicroseconds(1750);
  delay(deg * 5.5); 
}

void goForward(){
//Serial.println("Forward");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}
void moveIn(){
 // Serial.println("Move In");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(FORWARD_SPEED-100);
}
void moveOut(){
  //Serial.println("Move Out");
  leftMotor.writeMicroseconds(FORWARD_SPEED-100);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}

void checkCube() {
  
}

