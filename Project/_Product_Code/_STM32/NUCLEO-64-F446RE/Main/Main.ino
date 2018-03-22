
//Main routine

//Compile Options and Reqs:
//  Board: Nucleo-64
//  Part Number: F446RE
//  Upload Method: STLink

#include <Wire.h>
#include <Stream.h>
#include <SPI.h>


//pin assignments
#define RIGHT_MOTOR PC7
#define LEFT_MOTOR  PA9

#define CUBE_INTAKE_1 PA5
#define CUBE_INTAKE_2 PA6

#define PYR_INTAKE_1 PA7
#define PYR_INTAKE_2 PB6

#define LR_ULTRASONIC_IN PC1
#define LR_ULTRASONIC_OUT PC0
#define LF_ULTRASONIC_IN PA4
#define LF_ULTRASONIC_OUT PB0
#define F_ULTRASONIC_IN PA0
#define F_ULTRASONIC_OUT PA1

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
//IR input on USART3

//Program Parameters
#define FORWARD_SPEED 1700
#define REVERSE_SPEED 1300
#define TURN_AXIS_F 1750
#define TURN_AXIS_R 1250

#define PYR_INTAKE_UP 180 //Arbitrary Number for now
#define PYR_INTAKE_DOWN 0 //Arbitrary Number for now

#define CUBE_INTAKE_OPEN 180 //Arbitrary Number for now
#define CUBE_INTAKE_CLOSE 0 //Arbitrary Number for now

#define WALL_LOWER_THRESHOLD 5
#define WALL_UPPER_THRESHOLD 10
#define TURN_THRESHOLD 10

Servo leftMotor;
Servo rightMotor;

int cubeRetrieved = 0;
char led;

long LR_ultrasonic_dist;
long LF_ultrasonic_dist;
long F_ultrasonic_dist;
unsigned long LRecho;
unsigned long LFecho;
unsigned long Fecho;


//Functions
void pingLR(){
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(LR_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LR_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  LRecho = pulseIn(LR_ULTRASONIC_OUT, HIGH, 10000);
  if(LRecho) LR_ultrasonic_dist = LRecho;
}

void pingLF(){
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(LF_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(LF_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  LFecho = pulseIn(LF_ULTRASONIC_OUT, HIGH, 10000);
  if(LFecho) LF_ultrasonic_dist = LFecho;
}

void pingF(){
  //Ping Ultrasonic
  //Send the Ultrasonic Range Finder a 10 microsecond pulse per tech spec
  digitalWrite(F_ULTRASONIC_IN, HIGH);
  delayMicroseconds(10);  //The 10 microsecond pause where the pulse in "high"
  digitalWrite(F_ULTRASONIC_IN, LOW);
  //use command pulseIn to listen to Ultrasonic_Data pin to record the
  //time that it takes from when the Pin goes HIGH until it goes LOW 
  Fecho = pulseIn(F_ULTRASONIC_OUT, HIGH, 10000);
  if(Fecho) F_ultrasonic_dist = Fecho;
}

void TurnOnAxis(){
  leftMotor.writeMicroseconds(TURN_AXIS_R);
  rightMotor.writeMicroseconds(TURN_AXIS_F);
  delay(1000); 
}

void goForward(){
//Serial.println("Forward");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}
void moveIn(){
 // Serial.println("Move In");
  leftMotor.writeMicroseconds(FORWARD_SPEED);
  rightMotor.writeMicroseconds(1500);
}
void moveOut(){
  //Serial.println("Move Out");
  leftMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(FORWARD_SPEED);
}


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

  TwoWire Wire11;
  TwoWire Wire22;

  Wire11.begin();
  Wire22.begin();

  pinMode(LR_ULTRASONIC_IN, OUTPUT);
  pinMode(LF_ULTRASONIC_IN, OUTPUT);
  pinMode(F_ULTRASONIC_IN, OUTPUT);
  pinMode(LR_ULTRASONIC_OUT, INPUT);
  pinMode(LF_ULTRASONIC_OUT, INPUT);
  pinMode(F_ULTRASONIC_OUT, INPUT);

  pinMode(LEFT_MOTOR, OUTPUT);
  pinMode(RIGHT_MOTOR, OUTPUT);
  leftMotor.attach(LEFT_MOTOR);
  rightMotor.attach(RIGHT_MOTOR);

  attachInterrupt(digitalPinToInterrupt(HALL_EFFECT), magnetDetected, CHANGE);
  attachInterrupt(digitalPinToInterrupt(REED_SW), magnetDetected, CHANGE);
  attachInterrupt(digitalPinToInterrupt(LF_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(LR_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(RF_LIMIT_SW), lmswitch, FALLING);
  attachInterrupt(digitalPinToInterrupt(RR_LIMIT_SW), lmswitch, FALLING);
}


void loop(){
  if (!cubeRetrieved) {
    pingLR();
    pingLF();
    pingF();
  
    if(abs(LF_ultrasonic_dist - LR_ultrasonic_dist) <= 50){
      goForward();
    }
    else if(LF_ultrasonic_dist > LR_ultrasonic_dist){
      moveIn();
    }
    else{
      moveOut();
    }
  
    if(F_ultrasonic_dist < 1000){
      TurnOnAxis();
    }
  }
  else {
    if (Serial.available()) {
      led = Serial3.read(); // Attach IR sensor to serial 3
    }
  }
}



