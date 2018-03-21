
//Main routine

//Compile Options and Reqs:
//  Board: Nucleo-64
//  Part Number: F446RE
//  Upload Method: STLink



#include <Wire.h>
#include <Stream.h>

//pin assignments
#define RIGHT_MOTOR PC7
#define LEFT_MOTOR  PA9

#define CUBE_INTAKE_1 PA5
#define CUBE_INTAKE_2 PA6

#define PYR_INTAKE_1 PA7
#define PYR_INTAKE_2 PB6

#define HALL_EFFECT PB1
#define REED_SW PC4
#define IR_CONTROL PB12
#define LF_LIMIT_SW PB13
#define LR_LIMIT_SW PB15
#define RF_LIMIT_SW PB14
#define RR_LIMIT_SW PB2

//Ultrasonic input on USART2
//Compass input on I2C2
//Encoder input on I2C3

//Program Parameters
#define FORWARD_SPEED 1700
#define REVERSE_SPEED 1300
#define TURN_AXIS_F 1600
#define TURN_AXIS_R 1400

#define PYR_INTAKE_UP 180 //Arbitrary Number for now
#define PYR_INTAKE_DOWN 0 //Arbitrary Number for now

#define CUBE_INTAKE_OPEN 180 //Arbitrary Number for now
#define CUBE_INTAKE_CLOSE 0 //Arbitrary Number for now

//ISRs
void lmswitch(){
  
}

void magnetDetected(){
  
}

void setup(){
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);
  Serial4.begin(9600);
  Serial5.begin(9600);
  Serial6.begin(9600);
  
  Wire.begin();

  TwoWire Wire1;
  TwoWire Wire2;

  Wire1.begin();
  Wire2.begin();



  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT), magnetDetected, CHANGE);
  attachInterrupt(digitalPinToInterrupt(REED_SW), magnetDetected, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LF_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(LR_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(RF_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(RR_LIMIT_SW), lmswitch, FALLING);
  
}

void loop(){
  
}



